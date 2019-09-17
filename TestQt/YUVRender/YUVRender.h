#pragma once

#include <QtWidgets/QWidget>
#include "ui_YUVRender.h"

class YUVRender : public QWidget
{
	Q_OBJECT

public:
	YUVRender(QWidget *parent = Q_NULLPTR);
public slots:
	void onClickButton();
private:
	Ui::YUVRenderClass ui;
};
