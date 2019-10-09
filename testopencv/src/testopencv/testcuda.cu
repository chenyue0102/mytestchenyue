#ifndef _TESTCUDA_CU_
#define _TESTCUDA_CU_
// CUDA utilities and system includes
#include <cuda_runtime.h>
#include <helper_cuda.h>       // CUDA device initialization helper functions

__global__ 
void fill(int *pc, int width, int height, int totalThreads)
{
	int y = blockIdx.x * blockDim.x + threadIdx.x;
	int *tmp = pc + (width* y);
	for (int x = 0; x < width; x++)
	{
		tmp[x] = (y << 16) + x;
	}
	y += totalThreads;
	if (y < height)
	{
		tmp = pc + (width* y);
		for (int x = 0; x < width; x++)
		{
			tmp[x] = (y << 16) + x;
		}
	}
}
extern "C" void testcuda(int width, int height, int nthreads)
{
	int *p = new int[width * height]();
	int *pc = 0;
	checkCudaErrors(cudaMalloc(&pc, sizeof(int) * width * height));
	checkCudaErrors(cudaMemcpy(pc, p, sizeof(int) * width * height, cudaMemcpyHostToDevice));

	int totalThreads = height / nthreads * nthreads;
	fill << <height / nthreads, nthreads, 0 >> > (pc, width, height, totalThreads);

	checkCudaErrors(cudaDeviceSynchronize());
	cudaMemcpy(p, pc, sizeof(int)* width * height, cudaMemcpyDeviceToHost);

	for (int y = 0; y < height; y++)
	{
		int *tmp = p + (width * y);
		for (int x = 0; x < width; x++)
		{
			int o = (y << 16) + x;
			int r = tmp[x];
			if (o != r)
			{
				printf("error x=%d y=%d r=%d", x, y, r);
			}
		}
	}

	cudaFree(pc);
	delete[]p;
}
#endif