#include "testqtopencv.h"
#include <vector>
#include <iostream>
#include <QtWidgets/QApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/core/cuda.hpp>
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaimgproc.hpp>
#include "CUDACache.h"

void test()
{
	cv::Point2i pi1(1, 2);
	cv::Point2i pi2(3, 4);
	int i1 = pi1.dot(pi2);
	int i2 = pi2.cross(pi2);
	cv::Scalar sl(1, 2, 3, 4);
	cv::Rect rc(0, 0, 1, 1);
	rc += cv::Point2i(1,1);
	rc += cv::Size(2, 2);

	int a[2][3] =
	{
		{1,2,3},
		{4,5,6,},
	};
	std::vector<int> av;
	av.insert(av.end(), (int*)(a), (int*)(a) + 6);
	cv::Mat m;
	m.create(2, 3, CV_32FC3);
	m.setTo(cv::Scalar(1, 2, 3));
	cv::Vec3f v00 =  m.at<cv::Vec3f>(1, 2);
	float f0 = v00[0];
	float f1 = v00[1];
	float f2 = v00[2];

	cv::Mat m2(3, 3, CV_8UC1);
	int index = 0;
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			m2.at<uchar>(row, col) = index++;
		}
	}
	cv::Mat m3(m2, cv::Range(1, 3), cv::Range(1, 3));
	for (int row = 0; row < m3.rows; row++)
	{
		for (int col = 0; col < m3.cols; col++)
		{
			uchar c = m3.at<uchar>(row, col);
			//printf("%c", c);
		}
	}

	//设置标准矩阵，多维的情况下，只有第一个维度是1，其余是0
	cv::Mat m4 = cv::Mat::eye(3, 3, CV_32SC2);
	int i4 = m4.at<cv::Vec2i>(0, 0)[0];
	cv::MatIterator_<cv::Vec2i> it = m4.begin<cv::Vec2i>();
	while (it != m4.end<cv::Vec2i>())
	{
		(*it)[0] = 2;
		(*it)[1] = 3;
		++it;
	}
	cv::Mat mcol = m2.col(0);
	for (int i = 0; i < mcol.rows; i++)
	{
		uchar v = mcol.at<uchar>(i);
		//printf("%c", v);
	}

	cv::Mat addMat1(2, 2, CV_8UC2);
	std::fill(addMat1.begin<cv::Vec2b>(), addMat1.end<cv::Vec2b>(), cv::Vec2b(200, 100));
	cv::Mat addMat2(2, 2, CV_8UC2);
	std::fill(addMat2.begin<cv::Vec2b>(), addMat2.end<cv::Vec2b>(), cv::Vec2b(100, 100));
	cv::Mat addMat3 = addMat1 - addMat2;
	cv::Mat addMat4 = addMat1 + cv::Scalar(1,2);
	uchar u1 = addMat4.at<cv::Vec2b>(1, 1)[0];
	uchar u2 = addMat4.at<cv::Vec2b>(1, 1)[1];

	float pMulMat1[] = { 1,2,3,4,5,6,7,8, 9,10, 11, 12,13,14,15,16 };
	float pMulMat2[] = { 1,2,3,4,5,6,7,8,9, 10, 11, 12,13,14,15,16 };
	cv::Mat mulMat1(2, 2, CV_32FC1, pMulMat1);
	cv::Mat mulMat2(2, 2, CV_32FC1, pMulMat2);
	cv::Mat mulMat3 = mulMat1.mul(mulMat2);//安元素相乘
	cv::Mat mulMat4 = mulMat1 * mulMat2;//矩阵乘法
	std::cout << mulMat1 << std::endl << mulMat2 << std::endl;
	std::cout << cv::format(mulMat3, cv::Formatter::FMT_DEFAULT) << std::endl;
	std::cout << mulMat4 << std::endl;
	uchar c = cv::saturate_cast<uchar>(128 + 265);
	cv::Mat getMat(2, 3, CV_32FC3);
	size_t total = getMat.total();//2*3
	size_t elemSize = getMat.elemSize();//32 / 8 * 3
	size_t elemSize1 = getMat.elemSize1();//32 / 8
	int type = getMat.type();//CV_32FC3
	type = CV_32FC3;
	int depth = getMat.depth();//CV_32F
	depth = CV_32F;
	int channels = getMat.channels();//C3
	cv::Size size = getMat.size();//height 2 width 3
	cv::Mat_<cv::Vec2i> someMat(2, 3, cv::Vec2i(0, 0));
	someMat(1, 1) = cv::Vec2i(1, 2);
	std::cout << someMat << std::endl;

	cv::Mat_<cv::Vec3b> colorMat(2, 3, cv::Vec3b(1, 2, 3));
	std::vector<cv::Mat_<uchar>> colorMats;
	cv::split(colorMat, colorMats); 
	std::cout << colorMat << std::endl;
	std::cout << colorMats[0] << std::endl << colorMats[1] << std::endl << colorMats[2] << std::endl;


	uchar colors[] =
	{
		1,2,3,4,5,
		6,7,8,9,10,
		11,12,13,14,15,
		16,17,18,19,20,
		21,22,23,24,25,
	};
	cv::Mat borderMat(5, 5, CV_8UC1, colors);
	int borderCol = cv::borderInterpolate(-2, 5, cv::BORDER_REFLECT101);
	int borderCol2 = cv::borderInterpolate(-2, 5, cv::BORDER_REFLECT);

	cv::Mat lenaMat = cv::imread("lena512color.tiff", cv::IMREAD_UNCHANGED);
	cv::Mat lenaGrayMat;
	cv::cvtColor(lenaMat, lenaGrayMat, cv::COLOR_BGR2GRAY);
	cv::Mat lenaBinMat, lenaBinMat2;
	cv::threshold(lenaGrayMat, lenaBinMat, 100., 255., cv::THRESH_BINARY);
	cv::adaptiveThreshold(lenaGrayMat, lenaBinMat2, 255., cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 5 , 0.);
	cv::imshow("lenaMat", lenaMat);
	cv::imshow("lenaGrayMat", lenaGrayMat);
	cv::imshow("lenaBinMat", lenaBinMat);
	cv::imshow("lenaBinMat2", lenaBinMat2);
	int kernels[] = 
	{
		-1, -1, -1,
		-1, 9, - 1,
		-1, -1, -1,
	};
	cv::Mat sharpMat(3, 3, CV_32SC1, kernels);
	cv::Mat lenaSharpMat;
	cv::filter2D(lenaMat, lenaSharpMat, -1, sharpMat);
	cv::imshow("lenaSharpMat", lenaSharpMat);
}
void testGPU()
{
	auto i = cv::cuda::getCudaEnabledDeviceCount();
	//auto cuda_face_cascade = cv::cuda::CascadeClassifier::create("C:/opencv/opencv/sources/data/haarcascades_cuda/haarcascade_frontalface_alt.xml");
	cv::Mat mat = cv::imread("2.jpg");
	cv::cuda::GpuMat gpuMat, outMat;
	gpuMat.upload(mat);
	cv::cuda::bilateralFilter(gpuMat, outMat, 20, 50, 250);

	cv::cuda::GpuMat gaussianMat, tmpMat, tmpMat2;
	//tmpMat = (outMat - gpuMat + 128);

	//cv::GaussianBlur(tmpMat, gaussianMat, cv::Size(w, h), sigmaX, sigmaY);
//tmpMat = origin + 2 * gaussianMat - 256;
	//m = (origin * (100 - opacity) + tmpMat * opacity) / 100;


	cv::Mat dMat;
	outMat.download(dMat);
	cv::imshow("dMat", dMat);
}
CUDACache g_CUDACache;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//test();
	//testGPU();
	g_CUDACache.init();
	testqtopencv w;
	w.show();
	return a.exec();
}
