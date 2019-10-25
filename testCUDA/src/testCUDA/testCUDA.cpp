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
int main()
{
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

