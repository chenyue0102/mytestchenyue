// testopencv.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace cv;
int main()
{
	Mat img = imread("lena512color.tiff");
	Mat img_gray;
	cvtColor(img, img_gray, COLOR_BGR2GRAY);

	std::vector<Rect> faces;
	CascadeClassifier face_cascade;
	bool ret = face_cascade.load("haarcascade_frontalface_alt.xml");
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 2, 0, Size(30, 30));

	Rect roi = faces[0];
	Mat head = img_gray(roi);

	namedWindow("test");
	imshow("test", head);
	waitKey(6000);
    return 0;
}

