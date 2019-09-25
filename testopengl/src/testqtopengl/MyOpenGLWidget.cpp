#include <assert.h>
#include "MyOpenGLWidget.h"


//varying vertex和fragment共享的数据，vertex修改后传递给fragment
//attribute 只能够再vertex中使用，一般用作顶带你坐标，法线，纹理坐标，顶点颜色等
//uniform 程序传递给vertex或者fragment的变量，一般用作变换矩阵，材质，光照和颜色等信息

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

	//顶点
	static const GLfloat ver[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f
	};

	//材质
	static const GLfloat tex[] = {
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
	};

	int attr = program.attributeLocation("vertexIn");
	//assert(0 != attr);
	//2标识顶点是二维，包含x,y
	glVertexAttribPointer(attr, 2, GL_FLOAT, 0, 0, ver);
	glEnableVertexAttribArray(attr);

	attr = program.attributeLocation("textureIn");
	//assert(0 != attr);
	glVertexAttribPointer(attr, 2, GL_FLOAT, 0, 0, tex);
	glEnableVertexAttribArray(attr);

	//储存tex_rgb的索引
	m_uni = program.uniformLocation("tex_rgb");
	//assert(0 != m_uni);

	//生成材质，设置材质缩放参数
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
