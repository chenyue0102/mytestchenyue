/*
直播答题动画播放
*/
#pragma once

#include <QQuickWidget>

class MyQuickWidget : public QQuickWidget
{
	Q_OBJECT

public:
	MyQuickWidget(QWidget *parent);
	~MyQuickWidget();
private:
	void setQmlSize();
protected:
	virtual void resizeEvent(QResizeEvent *event)override;
};
