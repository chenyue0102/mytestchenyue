// testFFT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <complex>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>

int bitlen(int N) {
	int n = 0;
	while ((N & 1) == 0) {
		n++;
		N >>= 1;
	}
	return n;
}

int reverse_bit(int n, int len) {
	int tmp = 0;
	while (len--) {
		tmp += ((n & 1) << len);
		n >>= 1;
	}
	return tmp;
}

void resort(std::vector<std::complex<double>> &x, int N) {
	std::vector<std::complex<double>> v(x);

	int len = bitlen(N);
	for (int i = 0; i < N; i++) {
		x[i] = v[reverse_bit(i, len)];
	}
}

void FFT(std::vector<std::complex<double>> &x) {
	int N = x.size();
	int r = bitlen(N);

	std::vector<std::complex<double>> W(N);

	for (int i = 0; i < N; i++) {
		double angle = -i * 2 * M_PI / N;
		W[i] = std::complex<double>(cos(angle), sin(angle));
	}

	for (int k = 0; k < r; k++) {
		for (int j = 0; j < (1 << k); j++) {
			int butterfly = 1 << (r - k);
			int p = j * butterfly;
			int s = p + butterfly / 2;
			for (int i = 0; i < butterfly / 2; i++) {
				std::complex<double> c = x[i + p] + x[i + s];
				x[i + s] = (x[i + p] - x[i + s])* W[i * (1 << k)];
				x[i + p] = c;
			}
		}
	}

	resort(x, N);
}

void IFFT(std::vector<std::complex<double>> &x) {
	int N = x.size();
	int r = bitlen(N);

	std::vector<std::complex<double>> W(N);

	for (int i = 0; i < N; i++) {
		double angle = i * 2 * M_PI / N;
		W[i] = std::complex<double>(cos(angle), sin(angle));
	}

	for (int k = 0; k < r; k++) {
		for (int j = 0; j < (1 << k); j++) {
			int buterfly = 1 << (r - k);
			int p = j * buterfly;
			int s = p + buterfly / 2;
			for (int i = 0; i < buterfly / 2; i++) {
				std::complex<double> c = x[i + p] + x[i + s];
				x[i + s] = (x[i + p] - x[i + s]) * W[i * (1 << k)];
				x[i + p] = c;
			}
		}
	}
	resort(x, N);
	for (int i = 0; i < N; i++) {
		x[i] /= N;
	}
}

int main()
{
    std::cout << "Hello World!\n"; 
	std::vector<std::complex<double>> array;
	for (int i = 0; i < 64; i++) {
		std::complex<double> c(i, 0);
		array.push_back(c);
	}
	FFT(array);
	IFFT(array);
}


