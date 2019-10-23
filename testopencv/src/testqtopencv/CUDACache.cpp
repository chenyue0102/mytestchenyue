#include "CUDACache.h"
#include <opencv2/cudafilters.hpp>

struct GaussianFilterParam
{
	int srcType;
	int dstType;
	cv::Size ksize;
	double sigma1;
	double sigma2;
	int rowBorderMode;
	int columnBorderMode;

	bool operator==(const GaussianFilterParam &r)
	{
		return (srcType == r.srcType)
			&& (dstType == r.dstType)
			&& (ksize == r.ksize)
			&& (sigma1 == r.sigma1)
			&& (sigma2 == r.sigma2)
			&& (rowBorderMode == r.rowBorderMode)
			&& (columnBorderMode == r.columnBorderMode)
			;
	}
};
struct CUDACacheData
{
	cv::Ptr<cv::cuda::Filter> m_gaussFilter;
	GaussianFilterParam gaussFilterParam;
};
CUDACache::CUDACache()
	: m_pData(new CUDACacheData())
{
}


CUDACache::~CUDACache()
{
	delete m_pData;
	m_pData = nullptr;
}

void CUDACache::init()
{
}

void CUDACache::destroy()
{
}

cv::Ptr<cv::cuda::Filter> CUDACache::createGaussianFilter(int srcType, int dstType, cv::Size ksize, double sigma1, double sigma2, int rowBorderMode, int columnBorderMode)
{
	cv::Ptr<cv::cuda::Filter> ptr;
	GaussianFilterParam param;
	param.srcType = srcType;
	param.dstType = dstType;
	param.ksize = ksize;
	param.sigma1 = sigma1;
	param.sigma2 = sigma2;
	param.rowBorderMode = rowBorderMode;
	param.columnBorderMode = columnBorderMode;
	if (param == m_pData->gaussFilterParam
		&& m_pData->m_gaussFilter)
	{
		ptr = m_pData->m_gaussFilter;
	}
	else
	{
		ptr = cv::cuda::createGaussianFilter(srcType, dstType, ksize, sigma1, sigma2, rowBorderMode, columnBorderMode);
		m_pData->gaussFilterParam = param;
		m_pData->m_gaussFilter = ptr;
	}
	return ptr;
}
