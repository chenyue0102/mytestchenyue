#pragma once

#include "BaseWidget.h"
#include "ui_DlibDetectWidget.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_loader/load_image.h>
#include <dlib/dnn/loss.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/opencv.h>

template <long num_filters, typename SUBNET> using con5d = dlib::con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET> using con5 = dlib::con<num_filters, 5, 5, 1, 1, SUBNET>;

template <typename SUBNET> using downsampler = dlib::relu<dlib::affine<con5d<32, dlib::relu<dlib::affine<con5d<32, dlib::relu<dlib::affine<con5d<16, SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5 = dlib::relu<dlib::affine<con5<45, SUBNET>>>;

using net_type = dlib::loss_mmod<dlib::con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<dlib::input_rgb_image_pyramid<dlib::pyramid_down<6>>>>>>>>;
class DlibDetectWidget : public BaseWidget
{
	Q_OBJECT

public:
	DlibDetectWidget(QWidget *parent = Q_NULLPTR);
	~DlibDetectWidget();
public:
	virtual void coverImage(const cv::Mat &origin, cv::Mat &m, std::vector<cv::Rect> &rcs)override;
	virtual void coverImage(const cv::cuda::GpuMat &origin, cv::cuda::GpuMat &m, std::vector<cv::Rect> &rcs)override;
public Q_SLOTS:
	void loadFile();
private:
	Ui::DlibDetectWidget ui;
	dlib::frontal_face_detector m_cpuDetector;
	net_type m_gpuDetector;
	bool m_bLoadCascade;
};
