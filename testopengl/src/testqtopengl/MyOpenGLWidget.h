#pragma once
#include <QOPenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <QImage>

class MyOpenGLWidget 
	: public QOpenGLWidget
	, public QOpenGLFunctions
{
public:
	MyOpenGLWidget(QWidget *parent = 0);
	~MyOpenGLWidget();
protected:
	virtual void initializeGL();
	virtual void paintGL();
private:
	QGLShaderProgram program;
	GLuint m_uni = 0;
	GLuint m_tex = 0;
	QImage m_img;
	int m_width = 100;
	int m_height = 50;
};

