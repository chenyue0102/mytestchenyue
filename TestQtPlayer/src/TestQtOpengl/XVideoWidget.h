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
	//��ʼ��GL
	virtual void initializeGL()override;

	//ˢ����ʾ
	virtual void paintGL()override;

	//���ڴ�С�仯
	virtual void resizeGL(int width, int height)override;
private:
	//shader����
	QGLShaderProgram program;
	//shader��yuv������ַ
	GLuint unis[3] = { 0 };
	//opengl��texture��ַ
	GLuint texs[3] = { 0 };

	//�����ڴ�ռ�
	unsigned char *datas[3] = { 0 };

	int width = 240;
	int height = 128;
};
