#pragma once
#include <QOPenGLWidget>
#include <QOpenGLFunctions>
#include <QGLShaderProgram>
#include <QImage>
#include <QOpenGLTexture>
#include <QTimer>

class MyOpenGLWidget 
	: public QOpenGLWidget
	, public QOpenGLFunctions
{
	Q_OBJECT
public:
	MyOpenGLWidget(QWidget *parent = 0);
	~MyOpenGLWidget();
protected:
	virtual void initializeGL();
	virtual void paintGL();
public slots:
	void onTranslate();
private:
	QGLShaderProgram program;
	GLuint m_uni = 0;
	GLuint m_tex = 0;
	QImage m_img;
	int m_width = 100;
	int m_height = 50;
	QOpenGLTexture m_texture;
	float m_translateX = -1.0f;
	QTimer m_timer;
};

