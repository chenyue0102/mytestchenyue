#ifndef _VIDEO_RENDER_WIDGET_H_
#define _VIDEO_RENDER_WIDGET_H_
#include <QOPenGLWidget>
#include <QOpenGLFunctions>


class VideoRenderWidgetData;
class VideoRenderWidget
	: public QOpenGLWidget
	, public QOpenGLFunctions
{
	Q_OBJECT

public:
	VideoRenderWidget(QWidget *parent = 0);
	~VideoRenderWidget();
public:
	void setVideoInfo(int width, int height);
	void setData(const void *data, int len);
protected:
	virtual void initializeGL()override;
	virtual void paintGL()override;
protected:
	bool event(QEvent *event)override;
private:
	void innerInit();
private:
	VideoRenderWidgetData *m_pData;
};
#endif