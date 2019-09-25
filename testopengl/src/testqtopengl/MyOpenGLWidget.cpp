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
	uniform mat4 matrix;
	void main()
	{
		gl_Position = matrix * vertexIn;
		textureOut = textureIn;
	}
);

const char *fsrc = GET_STR(
	out  varying vec4 outColor;
	varying vec2 textureOut;
	uniform sampler2D tex_rgb;
	void main()
	{
		vec4 clr = texture2D(tex_rgb, textureOut).rgba;
		/*if (clr.a <= 0.0)*/
		/*	discard;*/
		outColor = clr;
	}
);

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
	, m_texture(QOpenGLTexture::Target2D)
{
	QImage img(m_width, m_height, QImage::Format_ARGB32_Premultiplied);
	img.fill(QColor(0, 0, 0, 0));

	QTextOption option(Qt::AlignLeft | Qt::AlignTop);
	option.setWrapMode(QTextOption::WordWrap);

	QPainter painter;
	painter.begin(&img);
	painter.setPen(QColor(255, 255, 255, 80));
	painter.drawText(QRect(0, 0, m_width, m_height / 2), "hello world 0123456789", option);
	painter.end();

	m_img = img;

	m_timer.setInterval(30);
	connect(&m_timer, SIGNAL(timeout()), SLOT(onTranslate()));
}


MyOpenGLWidget::~MyOpenGLWidget()
{
	glDeleteTextures(1, &m_tex);
}

void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();

	m_texture.setData(m_img);
	m_texture.setMinificationFilter(QOpenGLTexture::Linear);
	m_texture.setMagnificationFilter(QOpenGLTexture::Linear);
	m_texture.setWrapMode(QOpenGLTexture::Repeat);

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

	m_timer.start();
}

void MyOpenGLWidget::paintGL()
{
	//���û��
	glEnable(GL_BLEND);
	//GL_ONE_MINUS_SRC_COLOR
	//GL_ONE_MINUS_SRC_ALPHA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//���Ʊ���ɫ
	glPolygonMode(GL_FRONT, GL_FILL);//�������
	//glPolygonMode(GL_BACK, GL_FILL);//�������
	glFrontFace(GL_CCW);//��ʱ��Ϊ����
	//���ƶ����
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();

	/*glColor3f(0.0f, 1.0f, 0.0f);
	m_texture.bind();
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, 1.0f);
	glEnd();
	m_texture.release();*/

	QMatrix4x4 m;
	m.translate(m_translateX, -0.8f, 0.0f);
	m.scale(0.1, 0.1, 1);
	program.bind();
	program.setUniformValue("matrix", m);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_img.bits());
	glUniform1i(m_uni, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	program.release();

	
}

void MyOpenGLWidget::onTranslate()
{
	m_translateX += 0.003;
	if (m_translateX >= 1.0)
	{
		m_translateX = -1.0f;
	}
	update();
}