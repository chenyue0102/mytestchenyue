// testopencv.cpp : 定义控制台应用程序的入口点。
//
#include <minmax.h>
#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
using namespace cuda;
int main()
{
	auto i = getCudaEnabledDeviceCount();
	CascadeClassifier eye_cascade;
	eye_cascade.load("haarcascade_eye.xml");
	CascadeClassifier face_cascade;
	bool ret = face_cascade.load("haarcascade_frontalface_alt.xml");

	Mat img = imread("lena512color.tiff");
	
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0, Size(30, 30));


	//Rect roi = faces[0];
	//Mat head = img_gray(roi);

	std::vector<Rect> eyes;
	eye_cascade.detectMultiScale(img_gray, eyes);

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
	for (auto &r : eyes)
	{
		rectangle(img, r.tl(), r.br(), Scalar(0, 0, 255));
	}
	
	namedWindow("test");
	imshow("test", img);
	waitKey(60000);
    return 0;
}

