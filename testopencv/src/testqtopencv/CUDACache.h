#pragma once
#include <opencv2/cudafilters.hpp>

struct CUDACacheData;
class CUDACache
{
public:
	CUDACache();
	~CUDACache();
public:
	void init();
	void destroy();
public:
	cv::Ptr<cv::cuda::Filter> createGaussianFilter(int srcType, int dstType, cv::Size ksize,
		double sigma1, double sigma2 = 0,
		int rowBorderMode = cv::BORDER_DEFAULT, int columnBorderMode = -1);
private:
	CUDACacheData *m_pData;
};

