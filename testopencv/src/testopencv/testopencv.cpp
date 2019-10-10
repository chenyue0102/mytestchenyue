// testopencv.cpp : 定义控制台应用程序的入口点。
//
#include <minmax.h>
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/imgproc/types_c.h>

// CUDA utilities and system includes
#include <cuda_runtime.h>
#include <helper_cuda.h>       // CUDA device initialization helper functions


using namespace std;
using namespace cv;
using namespace cuda;
void detectAndDraw(Mat& img,
	cv::CascadeClassifier& cascade,
	double scale);
Mat mergeImage(Mat &left, Mat &right)
{
	Size size(left.cols + right.cols, max(left.rows, right.rows));
	Mat merge;

	merge.create(size, CV_MAKETYPE(left.depth(), 3));
	merge = Scalar::all(0);

	Mat out_left = merge(Rect(0, 0, left.cols, left.rows));
	Mat out_right = merge(Rect(left.cols, 0, right.cols, right.rows));
	left.copyTo(out_left);
	right.copyTo(out_right);
	return merge;
}
Mat test(Mat &src, int value1, int value2);

int FMax(const int X, const int Y)
{
	return (X < Y ? Y : X);
}

int FMin(const int X, const int Y)
{
	return (Y < X ? Y : X);
}
Mat white(Mat& tmp, int value)
{
	Mat bitmap = tmp.clone();
	double  highlights_add[256], highlights_sub[256];
	double  midtones_add[256], midtones_sub[256];
	double  shadows_add[256], shadows_sub[256];

	//初始化转换数组
	for (int i = 0; i < 256; i++)
	{
		highlights_add[i] = shadows_sub[255 - i] = (1.075 - 1 / ((double)i / 16.0 + 1));
		midtones_add[i] = midtones_sub[i] = 0.667 * (1 - (((double)i - 127.0) / 127.0)*(((double)i - 127.0) / 127.0));
		shadows_add[i] = highlights_sub[i] = 0.667 * (1 - (((double)i - 127.0) / 127.0)*(((double)i - 127.0) / 127.0));
	}
	int red, green, blue;
	unsigned char r_lookup[256], g_lookup[256], b_lookup[256];

	for (int i = 0; i < 256; i++)
	{
		red = i;
		green = i;
		blue = i;

		red += (int)(value * shadows_sub[red] + value * midtones_add[red] + value * highlights_sub[red]);
		red = FMax(0, FMin(0xFF, red));

		green += (int)(value * shadows_sub[green] + value * midtones_add[green] + value * highlights_sub[green]);
		green = FMax(0, FMin(0xFF, green));

		blue += (int)(value * shadows_sub[blue] + value * midtones_add[blue] + value * highlights_sub[blue]);
		blue = FMax(0, FMin(0xFF, blue));

		r_lookup[i] = (unsigned char)red;
		g_lookup[i] = (unsigned char)green;
		b_lookup[i] = (unsigned char)blue;
	}

	for (int row = 0; row < bitmap.rows; row++)
	{
		for (int col = 0; col < bitmap.cols; col++)
		{
			bitmap.at<Vec3b>(row, col)[0] = b_lookup[bitmap.at<Vec3b>(row, col)[0]];
			bitmap.at<Vec3b>(row, col)[1] = g_lookup[bitmap.at<Vec3b>(row, col)[1]];
			bitmap.at<Vec3b>(row, col)[2] = r_lookup[bitmap.at<Vec3b>(row, col)[2]];
		}
	}
	return bitmap;
}

extern "C"
{
	extern void testcuda(int width, int height, int nthreads);
}
int main()
{
	int dev = 0;
	cudaDeviceProp devProp;
	checkCudaErrors(cudaGetDeviceProperties(&devProp, dev));
	std::cout << "使用GPU device " << dev << ": " << devProp.name << std::endl;
	std::cout << "SM的数量：" << devProp.multiProcessorCount << std::endl;
	std::cout << "每个线程块的共享内存大小：" << devProp.sharedMemPerBlock / 1024.0 << " KB" << std::endl;
	std::cout << "每个线程块的最大线程数：" << devProp.maxThreadsPerBlock << std::endl;
	std::cout << "每个EM的最大线程数：" << devProp.maxThreadsPerMultiProcessor << std::endl;
	std::cout << "每个EM的最大线程束数：" << devProp.maxThreadsPerMultiProcessor / 32 << std::endl;
	testcuda(100, 200, devProp.maxThreadsPerMultiProcessor / 32);
	auto i = getCudaEnabledDeviceCount();
	/*
	cv::cuda::DeviceInfo di;
	bool b = di.isCompatible();
	*/
	//CascadeClassifier eye_cascade;
	//eye_cascade.load("haarcascade_eye.xml");
	cv::CascadeClassifier face_cascade;
	bool ret = face_cascade.load("C:/opencv/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");

	//auto cuda_face_cascade = cv::cuda::CascadeClassifier::create("C:/opencv/opencv/sources/data/haarcascades_cuda/haarcascade_frontalface_alt.xml");

	//Mat img = imread("lena512color.tiff");
	Mat origin_img = imread("2.jpg");
	Mat img = origin_img.clone();
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0, Size(30, 30));
	//rectangle(img, faces[0], Scalar(255, 0, 0));

	detectAndDraw(img, face_cascade, 1.0);
	//img = test(img, 3, 3);

	Mat w = white(img, 20);

	//Rect roi = faces[0];
	//Mat head = img_gray(roi);

	//std::vector<Rect> eyes;
	//eye_cascade.detectMultiScale(img_gray, eyes);

	/*
	Mat eye_img_left = img(eyes[0]);
	Mat eye_img_right = img(eyes[1]);

	Size size(eye_img_left.cols + eye_img_right.cols, max(eye_img_left.rows, eye_img_right.rows));

	Mat eye_merge;
	eye_merge.create(size, CV_MAKETYPE(eye_img_left.depth(), 3));
	eye_merge = Scalar::all(0);

	Mat out_left = eye_merge(Rect(0, 0, eye_img_left.cols, eye_img_left.rows));
	Mat out_right = eye_merge(Rect(eye_img_left.cols, 0, eye_img_right.cols, eye_img_right.rows));
	eye_img_left.copyTo(out_left);
	eye_img_right.copyTo(out_right);
	*/
	/*for (auto &r : eyes)
	{
		rectangle(img, r.tl(), r.br(), Scalar(0, 0, 255));
	}*/
	
	namedWindow("test");
	imshow("test", mergeImage(mergeImage(origin_img, img), w));
	waitKey(60000);
    return 0;
}

Mat test(Mat &src, int value1, int value2)
{
	int dx = value1 * 5;    //双边滤波参数之一
	double fc = value1*12.5; //双边滤波参数之一
	int p = 50;//透明度
	Mat temp1, temp2, temp3, temp4;

	//双边滤波
	bilateralFilter(src, temp1, dx, fc, fc);

	temp2 = (temp1 - src + 128);

	//高斯模糊
	GaussianBlur(temp2, temp3, Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

	temp4 = src + 2 * temp3 - 255;

	Mat dst = (src*(100 - p) + temp4*p) / 100;
	return dst;
}

void detectAndDraw(Mat& img,
	cv::CascadeClassifier& cascade,
	double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces;
	const static Scalar colors[] = { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255) };//用不同的颜色表示不同的人脸

	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);//将图片缩小，加快检测速度

	cvtColor(img, gray, CV_BGR2GRAY);//因为用的是类haar特征，所以都是基于灰度图像的，这里要转换成灰度图像
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//将尺寸缩小到1/scale,用线性插值
	//equalizeHist(smallImg, smallImg);//直方图均衡
	
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));

	vector<Rect> faces2;
	cascade.detectMultiScale(gray, faces2,
		1.1, 3, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		//| CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30));
	//rectangle(img, faces2[0], Scalar(255,0,0));

	bool isDetected = false;
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)
	{
		isDetected = true;
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center, left, right;
		Scalar color = colors[i % 8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//还原成原来的大小
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);


		left.x = center.x - radius;
		left.y = cvRound(center.y - radius*1.3);

		if (left.y<0)
		{
			left.y = 0;
		}

		right.x = center.x + radius;
		right.y = cvRound(center.y + radius*1.3);

		if (right.y > img.rows)
		{
			right.y = img.rows;
		}

		rectangle(img, left, right, Scalar(255, 0, 0));



		Mat roi = img(Range(left.y, right.y), Range(left.x, right.x));
		Mat dst;

		int value1 = 3, value2 = 1;

		int dx = value1 * 5;    //双边滤波参数之一  
		double fc = value1*12.5; //双边滤波参数之一  
		int p = 50;//透明度  
		Mat temp1, temp2, temp3, temp4;

		//双边滤波  
		bilateralFilter(roi, temp1, dx, fc, fc);

		temp2 = (temp1 - roi + 128);

		//高斯模糊  
		GaussianBlur(temp2, temp3, Size(2 * value2 - 1, 2 * value2 - 1), 0, 0);

		temp4 = roi + 2 * temp3 - 255;

		dst = (roi*(100 - p) + temp4*p) / 100;


		dst.copyTo(roi);
	}
}
