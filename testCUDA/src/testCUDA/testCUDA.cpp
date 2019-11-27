// testCUDA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <algorithm>
#include <cuda_runtime.h>
#include <helper_cuda.h>
#include "CalcTime.h"

extern "C"
{
	void testCPU(double *f, int width, int height);
	void testCUDA1(double *f, int width, int height);
	void testCUDA2(double *d, int width, int height);
	void testGridBlock();
}
template<typename T>
void MatMul(const T *A, const T *B, T *C, const int M, const int N, const int S)
{
	//C = A * B
	//A [M][N] 
	//B [N][S]
	//C [M][S]
	for (int m = 0; m < M; m++)
	{
		//A的m行 * B 的 s列 ，放入到c的 [m][s]
		for (int s = 0; s < S; s++)
		{
			int index = m * S + s;
			C[index] = T();
			for (int n = 0; n < N; n++)
			{
				C[index] += A[m * N + n] * B[n * S + s];
			}
		}
	}
}
template<typename T>
void MatAdd(const T *A, const T *B, T *C, const int M, const int N)
{
	//A[M][N]
	//B[M][N]
	//C[M][N]
	for (int m = 0; m < M; m++)
	{
		for (int n = 0; n < N; n++)
		{
			C[m * N + n] = A[m * N + n] + B[m * N + n];
		}
	}
}
#define M 3
#define N 3
#define S 1
typedef unsigned char uchar8;

void rgb2yuv(uchar8 r, uchar8 g, uchar8 b, uchar8 *y, uchar8 *u, uchar8 *v)
{
	*y = 0.299f * r + 0.587f * g + 0.114f * b;
	*u = -0.169f * r - 0.331f * g + 0.5f * b + 128;
	*v = 0.5f * r - 0.419f * g - 0.081f * b + 128;
}
static uchar8 clamp(int v)
{
	if (v > 255)
	{
		return 255;
	}
	else if (v < 0)
	{
		return 0;
	}
	else
	{
		return v;
	}
}

void yuv2rgb(uchar8 y, uchar8 u, uchar8 v, uchar8 * r, uchar8 * g, uchar8 * b)
{
	int tmp = y + 1.13983 * (v - 128);
	*r = clamp(tmp);

	tmp = y - 0.39465 * (u - 128) - 0.58060 * (v - 128);
	*g = clamp(tmp);

	tmp = y + 2.03211 * (u - 128);
	*b = clamp(tmp);
}

int main()
{

	double a[M][N] = {
		{ 0.299, 0.587,0.114 },
		{ -0.169, -0.331, 0.5},
		{0.5, -0.419,-0.081},
	};
	double b[N][S] = {
		{45},
		{55},
		{ 65 },
	};
	double dd = 2.0;
	dd = 0.1;
	bool bbc = 0.10000000000000001 == 0.1;
	double c[M][S] = { 0 };
	MatMul<double>((double*)a, (double*)b, (double*)c, M, N, S);
	double ad[M][1] = { {0},{128},{128} };
	MatAdd<double>((double*)c, (double*)ad, (double*)c, M, 1);
	uchar8 y, u, v;
	rgb2yuv(45, 55, 65, &y, &u, &v);

	testGridBlock();
	int width = 1024 * 5/5/10;
	int height = 512*5;
	int size = width * height;
	double *dArray = new double[size];
	std::fill(dArray, dArray + size, 123456.);
	CalcTime calcTime;
	int timeCPU = 0, timeGPU1 = 0, timeGPU2 = 0, timeGPU3 = 0;
	
	calcTime.start();
	testCPU(dArray, width, height);
	timeCPU = calcTime.endMs();
	
	calcTime.start();
	testCUDA1(dArray, width, height);
	timeGPU1 = calcTime.endMs();

	cudaHostRegister(dArray, size * sizeof(double), cudaHostRegisterPortable);
	calcTime.start();
	testCUDA1(dArray, width, height);
	timeGPU2 = calcTime.endMs();
	cudaHostUnregister(dArray);

	double *dArray2 = nullptr;
	checkCudaErrors(cudaMallocManaged(&dArray2, sizeof(double) * size));
	memcpy(dArray2, dArray, sizeof(double) * size);
	calcTime.start();
	testCUDA2(dArray2, width, height);
	timeGPU3 = calcTime.endMs();
	checkCudaErrors(cudaFree(dArray2));

	printf("CPU=%d CUDA1=%d CUDA2=%d CUDA3=%d", timeCPU, timeGPU1, timeGPU2, timeGPU3);
    return 0;
}

