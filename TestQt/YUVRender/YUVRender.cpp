#include "YUVRender.h"

YUVRender::YUVRender(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//ui.widget->setAttribute(Qt::WA_TranslucentBackground);
	//ui.widget->setAttribute(Qt::WA_NoSystemBackground, false);
	//ui.widget->setStyleSheet("QOpenGLWidget{background:rgb(255,0,0);}");
	ui.widget->setVideoInfo(1024, 768);
	connect(ui.pushButton, SIGNAL(clicked()), SLOT(onClickButton()));
}

void YUVRender::onClickButton()
{
	FILE *f = fopen("1.yuv", "rb");
	int len = 1024 * 768 * 3 / 2;
	unsigned char *data = new unsigned char[len];
	fread(data, 1, len, f);
	fclose(f);
	ui.widget->setData(data, len);
	ui.widget->asyncUpdate();
}