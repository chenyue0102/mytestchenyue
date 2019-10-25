#include "testdlib.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_loader/load_image.h>
#include <dlib/dnn/loss.h>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>

using namespace dlib;
template <long num_filters, typename SUBNET> using con5d = con<num_filters, 5, 5, 2, 2, SUBNET>;
template <long num_filters, typename SUBNET> using con5 = con<num_filters, 5, 5, 1, 1, SUBNET>;

template <typename SUBNET> using downsampler = relu<affine<con5d<32, relu<affine<con5d<32, relu<affine<con5d<16, SUBNET>>>>>>>>>;
template <typename SUBNET> using rcon5 = relu<affine<con5<45, SUBNET>>>;

using net_type = loss_mmod<con<1, 9, 9, 1, 1, rcon5<rcon5<rcon5<downsampler<input_rgb_image_pyramid<pyramid_down<6>>>>>>>>;
testdlib::testdlib(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	dlib::matrix<dlib::rgb_pixel> img;
	dlib::load_image(img, "2.jpg");
	auto detector = dlib::get_frontal_face_detector();
	std::vector<dlib::rectangle> faces = detector(img);

	net_type net;
	dlib::deserialize("mmod_human_face_detector.dat") >> net;
	std::vector<dlib::mmod_rect> faces2 = net(img);

	image_window *win = new image_window();

	win->set_image(img);

	//dlib::array2d<dlib::rgb_pixel> img;
	//dlib::assign_image()
}
