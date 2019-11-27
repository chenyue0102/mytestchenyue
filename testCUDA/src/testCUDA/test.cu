#ifndef _TEST_CU_
#define _TEST_CU_
#include <cuda_runtime.h>
#include <helper_cuda.h>

__device__
__host__
void calcValue(double *f, int width, int height, int row)
{
	f += row * width;
	for (int i = 0; i < width; i++)
	{
		for (int c = 0; c < 600; c++)
		{
			f[i] = std::pow(f[i], 2);
			f[i] = std::sqrt(f[i]);
		}
	}
}
__global__
void cudaCalc(double *f, int width, int height)
{
	int row = blockIdx.x * blockDim.x + threadIdx.x;
	if (row >= height)
	{
		return;
	}
	calcValue(f, width, height, row);
}
#define BLOCK_SIZE 32 * 2

extern "C" void testCUDA1(double *f, int width, int height)
{
	const int blockSize = BLOCK_SIZE;
	int gridSize = height / blockSize;
	if (height % blockSize != 0)
	{
		gridSize++;
	}
	double *fCuda = nullptr;
	int byteCount = sizeof(double) * width * height;
	checkCudaErrors(cudaMalloc(&fCuda, byteCount));
	checkCudaErrors(cudaMemcpy(fCuda, f, byteCount, cudaMemcpyHostToDevice));
	cudaCalc << <gridSize, blockSize >> > (fCuda, width, height);
	checkCudaErrors(cudaDeviceSynchronize());
	checkCudaErrors(cudaMemcpy(f, fCuda, byteCount, cudaMemcpyDeviceToHost));
	checkCudaErrors(cudaFree(fCuda));
}

extern "C" void testCUDA2(double *d, int width, int height)
{
	const int blockSize = BLOCK_SIZE;
	int gridSize = height / blockSize;
	if (height % blockSize != 0)
	{
		gridSize++;
	}
	cudaCalc << <gridSize, blockSize >> > (d, width, height);
	checkCudaErrors(cudaDeviceSynchronize());
}

extern "C" void testCPU(double *f, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		calcValue(f, width, height, i);
	}
}

__global__
void fillNumber(long long  *p)
{
	int blockId = blockIdx.x + (gridDim.x * blockIdx.y) + (gridDim.x * gridDim.y * blockIdx.z);
	int offset = threadIdx.x + (threadIdx.y * blockDim.x) + (blockDim.x * blockDim.y * threadIdx.z) + (blockId * blockDim.x * blockDim.y * blockDim.z);
	int item[] = { blockIdx.z, blockIdx.y, blockIdx.x, threadIdx.z, threadIdx.y, threadIdx.x };
	long long  value = 0;
	
	for (int i : item)
	{
		value += i;
		value *= 10;
	}
	value /= 10;
	p[offset] = value;
}

extern "C" void testGridBlock()
{
	long long data[2][3][4][5][6][7] = { 0 };
	long long  *p = 0;
	cudaMallocManaged(&p, sizeof(data));
	dim3 grid(4, 3, 2), block(7,6,5);
	fillNumber << <grid, block >> > (p);
	checkCudaErrors(cudaDeviceSynchronize());
	memcpy(data, p, sizeof(data));
}




extern "C" void testYUV2RGB()
{

}
#endif