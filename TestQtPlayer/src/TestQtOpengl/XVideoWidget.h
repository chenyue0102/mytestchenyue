#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>

class XVideoWidget 
	: public QOpenGLWidget
	, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	XVideoWidget(QWidget *parent);
	~XVideoWidget();
protected:
	//初始化GL
	virtual void initializeGL()override;

	//刷新显示
	virtual void paintGL()override;

	//窗口大小变化
	virtual void resizeGL(int width, int height)override;
private:
	//shader程序
	QGLShaderProgram program;
	//shader中yuv变量地址
	GLuint unis[3] = { 0 };
	//opengl的texture地址
	GLuint texs[3] = { 0 };

	//材质内存空间
	unsigned char *datas[3] = { 0 };

	int width = 240;
	int height = 128;
};
