#include <assert.h>
#include "MyOpenGLWidget.h"


//varying vertex��fragment��������ݣ�vertex�޸ĺ󴫵ݸ�fragment
//attribute ֻ�ܹ���vertex��ʹ�ã�һ���������������꣬���ߣ��������꣬������ɫ��
//uniform ���򴫵ݸ�vertex����fragment�ı�����һ�������任���󣬲��ʣ����պ���ɫ����Ϣ

#define GET_STR(x) #x

const char *vsrc = GET_STR(
	attribute vec4 vertexIn;
	attribute vec2 textureIn;
	varying vec2 textureOut;
	void main()
	{
		gl_Position = vertexIn;
		textureOut = textureIn;
	}
);

const char *fsrc = GET_STR(
	varying vec2 textureOut;
	uniform sampler2D tex_rgb;
	void main()
	{
		vec3 irgb = texture2D(tex_rgb, textureOut).rgb;
		gl_FragColor = vec4(irgb, 1.0);
	}
);
MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	QImage img(m_width, m_height, QImage::Format_ARGB32_Premultiplied);
	img.fill(QColor(0, 0, 0, 0));

	QTextOption option(Qt::AlignLeft | Qt::AlignTop);
	option.setWrapMode(QTextOption::WordWrap);

	QPainter painter;
	painter.begin(&img);
	painter.setPen(QColor(255, 0, 0));
	painter.drawText(QRect(0, 0, m_width, m_height), "hello world", option);
	painter.end();

	m_img = img;
}


MyOpenGLWidget::~MyOpenGLWidget()
{
	glDeleteTextures(1, &m_tex);
}

void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	bool ret = false;
	ret = program.addShaderFromSourceCode(QGLShader::Fragment, fsrc);
	assert(ret);
	ret = program.addShaderFromSourceCode(QGLShader::Vertex, vsrc);
	assert(ret);
	ret = program.link();
	assert(ret);

	//����
	static const GLfloat ver[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};

	//����
	static const GLfloat tex[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	int attr = program.attributeLocation("vertexIn");
	//assert(0 != attr);
	//2��ʶ�����Ƕ�ά������x,y
	glVertexAttribPointer(attr, 2, GL_FLOAT, 0, 0, ver);
	glEnableVertexAttribArray(attr);

	attr = program.attributeLocation("textureIn");
	//assert(0 != attr);
	glVertexAttribPointer(attr, 2, GL_FLOAT, 0, 0, tex);
	glEnableVertexAttribArray(attr);

	//����tex_rgb������
	m_uni = program.uniformLocation("tex_rgb");
	//assert(0 != m_uni);

	//���ɲ��ʣ����ò������Ų���
	glGenTextures(1, &m_tex);
	assert(0 != m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void MyOpenGLWidget::paintGL()
{
	program.bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_img.bits());
	glUniform1i(m_uni, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	program.release();
}
