#ifndef _MATCHPROCESS_CU_
#define _MATCHPROCESS_CU_
#include <cuda_runtime.h>
#include <helper_cuda.h>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudafilters.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CUDACache.h"

/*
cv::Mat gaussianMat, tmpMat, tmpMat2;
tmpMat = (m - origin + 128);

cv::GaussianBlur(tmpMat, gaussianMat, cv::Size(w, h), sigmaX, sigmaY);
tmpMat = origin + 2 * gaussianMat - 256;
m = (origin * (100 - opacity) + tmpMat * opacity) / 100;
*/

__device__
uchar saturate_cast(int v)
{
	return (uchar)((unsigned)v <= UCHAR_MAX ? v : v > 0 ? UCHAR_MAX : 0);
}

__global__
void doGaussianGPUFirst(const uchar *origin, const uchar *processed, uchar *result, int width, int height, int channels, int bytesPerLine)
{
	//tmpMat = (m - origin + 128);
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	if (row >= height)
	{
		return;
	}
	const uchar *orginTmp = origin + (bytesPerLine * row);
	const uchar *processedTmp = processed + (bytesPerLine * row);
	uchar *resultTmp = result + (bytesPerLine * row);
	for (int i = 0; i < width * channels; i++)
	{
		resultTmp[i] = saturate_cast((int)processedTmp[i] - (int)orginTmp[i] + 128);
	}
}

__global__
void doGaussianGPUSecond(const uchar *origin, const uchar *gaussian, uchar *result, int width, int height, int channels, int bytesPerLine, int opacity)
{
	/*
	tmpMat = origin + 2 * gaussianMat - 256;
	m = (origin * (100 - opacity) + tmpMat * opacity) / 100;
	*/
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	if (row >= height)
	{
		return;
	}
	const uchar *orginTmp = origin + (bytesPerLine * row);
	const uchar *gaussianTmp = gaussian + (bytesPerLine * row);
	uchar *resultTmp = result + (bytesPerLine * row);
	for (int i = 0; i < width * channels; i++)
	{
		int v = ((int)orginTmp[i] * (100 - opacity) + ((int)orginTmp[i] + 2 * (int)gaussianTmp[i] - 256) * opacity) / 100;
		resultTmp[i] = saturate_cast(v);
	}
}

extern CUDACache g_CUDACache;

#define BLOCK_SIZE 32 * 2

extern "C" void doGaussianGPU(const cv::cuda::GpuMat & origin, cv::cuda::GpuMat & m, int w, int h, double sigmaX, double sigmaY, int opacity)
{
	cv::cuda::GpuMat tmpMat(m.size(), m.type(), cv::Scalar(1,1,1)), gaussianMat(m.size(), m.type(), cv::Scalar(0, 0, 0));

	int width = origin.cols, height = origin.rows;
	int channels = origin.channels();
	int bytesPerLine = origin.step;

	const int blockSize = BLOCK_SIZE;
	int gridSize = height / blockSize;
	if (height % blockSize != 0)
	{
		gridSize++;
	}
	//tmpMat = (m - origin + 128);
	doGaussianGPUFirst << <gridSize, blockSize >> > (origin.data, m.data, tmpMat.data, width, height, channels, bytesPerLine);
	checkCudaErrors(cudaDeviceSynchronize());

	/*cv::Mat tt;
	tmpMat.download(tt);
	cv::imshow("tt", tt);*/

	//cv::GaussianBlur(tmpMat, gaussianMat, cv::Size(w, h), sigmaX, sigmaY);
	auto GaussianBlur = g_CUDACache.createGaussianFilter(tmpMat.type(), gaussianMat.type(), cv::Size(w, h), sigmaX, sigmaY);
	if (!GaussianBlur)
	{
		return;
	}
	GaussianBlur->apply(tmpMat, gaussianMat);

	/*
	tmpMat = origin + 2 * gaussianMat - 256;
	m = (origin * (100 - opacity) + tmpMat * opacity) / 100;
	*/
	doGaussianGPUSecond << <gridSize, blockSize >> > (origin.data, gaussianMat.data, m.data, width, height, channels, bytesPerLine, opacity);
	checkCudaErrors(cudaDeviceSynchronize());
}

__device__
void cudargb2yuv(uchar r, uchar g, uchar b, uchar *y, uchar *u, uchar *v)
{
	*y = 0.299f * r + 0.587f * g + 0.114f * b;
	*u = -0.169f * r - 0.331f * g + 0.5f * b + 128;
	*v = 0.5f * r - 0.419f * g - 0.081f * b + 128;
}

__device__
void cudayuv2rgb(uchar y, uchar u, uchar v, uchar * r, uchar * g, uchar * b)
{
	int tmp = y + 1.13983 * (v - 128);
	*r = saturate_cast(tmp);

	tmp = y - 0.39465 * (u - 128) - 0.58060 * (v - 128);
	*g = saturate_cast(tmp);

	tmp = y + 2.03211 * (u - 128);
	*b = saturate_cast(tmp);
}

__global__
void makeWhiteGPU(uchar *data, int width, int height, int channels, int bytesPerLine, const int *mapTable)
{
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	if (row >= height)
	{
		return;
	}
	uchar *dataTmp = data + (row * bytesPerLine);
	uchar y, u, v;
	
#if 0
	for (int i = 0; i < width * channels; i += 3)
	{
		cudargb2yuv(dataTmp[i + 2], dataTmp[i + 1], dataTmp[i + 0], &y, &u, &v);
		y = saturate_cast(mapTable[y]);
		cudayuv2rgb(y, u, v, &(dataTmp[i + 2]), &(dataTmp[i + 1]), &(dataTmp[i + 0]));
	}
#else
	for (int i = 0; i < width * channels; i++)
	{
		dataTmp[i] = mapTable[dataTmp[i]];
	}
#endif
	
}

extern "C" void doMakeWhiteGPU(cv::cuda::GpuMat & origin, const int *mapTable)
{
	int width = origin.cols, height = origin.rows;
	int channels = origin.channels();
	int bytesPerLine = origin.step;
	const int blockSize = BLOCK_SIZE;
	int gridSize = height / blockSize;
	if (height % blockSize != 0)
	{
		gridSize++;
	}
	
	makeWhiteGPU << <gridSize, blockSize >> > (origin.data, width, height, channels, bytesPerLine, mapTable);
	checkCudaErrors(cudaDeviceSynchronize());
}
#endif