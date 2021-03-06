#include "GL\glew.h"
#include <assert.h>
#include "MyOpenGLWidget.h"

#define CHECKERR\
if (GL_NO_ERROR != glGetError())\
	{\
		assert(false); \
	}

//varying vertex和fragment共享的数据，vertex修改后传递给fragment
//attribute 只能够再vertex中使用，一般用作顶带你坐标，法线，纹理坐标，顶点颜色等
//uniform 程序传递给vertex或者fragment的变量，一般用作变换矩阵，材质，光照和颜色等信息

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

QImage g_img;

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
	g_img.load("d:/1.png");
	g_img = g_img.convertToFormat(QImage::Format_RGB888);
}


MyOpenGLWidget::~MyOpenGLWidget()
{
	glDeleteTextures(1, &m_tex);
}
#include "FormatConver.h"

FormatConver g_f;
//void (GLAPIENTRY *GLDEBUGPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void GLAPIENTRY DEBUGPROC(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	qDebug() << message; return;
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes
	qDebug() << message;
}
void MyOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
	GLenum status = glewInit();
	assert(GLEW_OK == status);
	glEnable(GL_DEBUG_OUTPUT);
	//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(&DEBUGPROC, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

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

	m_timer.start();
}

void MyOpenGLWidget::paintGL()
{
#if 0
	//启用混合
	glEnable(GL_BLEND);
	//GL_ONE_MINUS_SRC_COLOR
	//GL_ONE_MINUS_SRC_ALPHA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//绘制背景色
	glPolygonMode(GL_FRONT, GL_FILL);//正面填充
	//glPolygonMode(GL_BACK, GL_FILL);//正面填充
	glFrontFace(GL_CCW);//逆时针为正面
	//绘制多边形
	glColor3f(0.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();

	QMatrix4x4 m;
	program.bind();
	program.setUniformValue("matrix", m);
	m_texture.bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	m_texture.release();
	program.release();

	
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
#endif

	//g_f.drawImage(g_img.constBits(), g_img.width(), g_img.height());
	//g_f.rgb2yuv();
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