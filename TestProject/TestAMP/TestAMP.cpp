// TestAMP.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <amp.h>
#include <iostream>

const int size = 5;
int main()
{
	int aCPP[] = { 1, 2, 3, 4, 5 };
	int bCPP[] = { 6, 7, 8, 9, 10 };
	int sumCPP[size];

	// Create C++ AMP objects.  
	concurrency::array_view<const int, 1> a(size, aCPP);
	concurrency::array_view<const int, 1> b(size, bCPP);
	concurrency::array_view<int, 1> sum(size, sumCPP);
	sum.discard_data();

	concurrency::parallel_for_each(
		// Define the compute domain, which is the set of threads that are created.  
		sum.extent,
		// Define the code to run on each thread on the accelerator.  
		[=](concurrency::index<1> idx) restrict(amp)
	{
		sum[idx] = a[idx] + b[idx];
	}
	);

	// Print the results. The expected output is "7, 9, 11, 13, 15".  
	for (int i = 0; i < size; i++) {
		std::cout << sum[i] << "\n";
	}
    return 0;
}

