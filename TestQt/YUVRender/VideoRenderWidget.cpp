#include <assert.h>
#include <mutex>
#include <QCoreApplication>
#include <QGLShaderProgram>
#include <QTimer>
#include "VideoRenderWidget.h"

#define GET_STR(x) #x

//vertexIn顶点坐标
//textureIn材质坐标
//varying 顶点shader与片元shader共享
//定点shader
const char *vString = GET_STR(
	attribute vec4 vertexIn;
	attribute vec2 textureIn;
	varying vec2 textureOut;
	void main(void)
	{
		gl_Position = vertexIn;
		textureOut = textureIn;
	}
);

//片元shader
//textureOut坐标
const char *fString = GET_STR(
	varying vec2 textureOut;
	uniform sampler2D tex_y;
	uniform sampler2D tex_u;
	uniform sampler2D tex_v;
	void main(void)
	{
		vec3 yuv;
		vec3 rgb;
		yuv.x = texture2D(tex_y, textureOut).r;
		yuv.y = texture2D(tex_u, textureOut).r - 0.5;
		yuv.z = texture2D(tex_v, textureOut).r - 0.5;
		rgb = mat3(1.0, 1.0, 1.0,
					0.0, -0.39465, 2.03211,
					1.13983, -0.58060, 0.0) * yuv;
		gl_FragColor = vec4(rgb, 1.0);
	}
);

#define A_VER 3
#define T_VER 4


class MyNotifyEvent : public QEvent
{
public:
	MyNotifyEvent(int type)
		: QEvent(static_cast<QEvent::Type>(type))
	{

	}
};

struct VideoRenderWidgetData
{
	std::mutex m_mutex;
	bool m_bInitedGL = false;
	//shader程序
	QGLShaderProgram program;
	//shader中yuv变量地址
	GLuint unis[3] = { 0 };
	//opengl的texture地址
	GLuint texs[3] = { 0 };

	int m_width = 0, m_height = 0;
	unsigned char *m_datas = nullptr;
	int m_len = 0;
	int evnetId = QEvent::registerEventType();
	QTimer timerUpdateFrame;
};
VideoRenderWidget::VideoRenderWidget(QWidget *parent)
	: QOpenGLWidget(parent)
	, m_pData(new VideoRenderWidgetData())
{
	auto &timerUpdateFrame = m_pData->timerUpdateFrame;
	timerUpdateFrame.setInterval(40);
	timerUpdateFrame.start();
	connect(&timerUpdateFrame, SIGNAL(timeout()), SLOT(update()));
}

VideoRenderWidget::~VideoRenderWidget()
{
	delete m_pData;
	m_pData = nullptr;
}

void VideoRenderWidget::setVideoInfo(int width, int height)
{
	std::lock_guard<std::mutex> lk(m_pData->m_mutex);

	auto &m_width = m_pData->m_width;
	auto &m_height = m_pData->m_height;
	auto &m_datas = m_pData->m_datas;
	auto &m_len = m_pData->m_len;

	if (m_width == width
		&& m_height == height)
	{
		return;
	}

	m_width = width;
	m_height = height;

	if (m_width > 0
		&& m_height > 0)
	{
		if (nullptr != m_datas)
		{
			delete[]m_datas;
			m_datas = nullptr;
		}
		m_len = m_width * m_height * 3 / 2;
		m_datas = new unsigned char[m_len];
		memset(m_datas, 0, m_len);

		QCoreApplication::postEvent(this, new MyNotifyEvent(m_pData->evnetId));
	}
}

void VideoRenderWidget::setData(const void * data, int len)
{
	std::lock_guard<std::mutex> lk(m_pData->m_mutex);

	auto &m_width = m_pData->m_width;
	auto &m_height = m_pData->m_height;
	auto &m_datas = m_pData->m_datas;
	auto &m_len = m_pData->m_len;

	do
	{
		if (m_width <= 0
			|| m_height <= 0)
		{
			assert(false);
			break;
		}
		if (len != m_len
			|| nullptr == data
			|| nullptr == m_datas)
		{
			assert(false);
			break;
		}
		memcpy(m_datas, data, len);
	} while (false);
}

void VideoRenderWidget::initializeGL()
{
	std::lock_guard<std::mutex> lk(m_pData->m_mutex);

	auto &program = m_pData->program;
	auto &unis = m_pData->unis;
	auto &texs = m_pData->texs;
	auto &m_bInitedGL = m_pData->m_bInitedGL;

	//初始化opengl 
	initializeOpenGLFunctions();

	bool ret = false;
	ret = program.addShaderFromSourceCode(QGLShader::Fragment, fString);
	assert(ret);

	ret = program.addShaderFromSourceCode(QGLShader::Vertex, vString);
	assert(ret);
	
	program.bindAttributeLocation("vertexIn", A_VER);
	program.bindAttributeLocation("textureIn", T_VER);

	ret = program.link();
	assert(ret);

	ret = program.bind();
	assert(ret);

	//传递顶点和材质坐标
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

	glVertexAttribPointer(A_VER, 2, GL_FLOAT, 0, 0, ver);
	glEnableVertexAttribArray(A_VER);

	glVertexAttribPointer(T_VER, 2, GL_FLOAT, 0, 0, tex);
	glEnableVertexAttribArray(T_VER);

	unis[0] = program.uniformLocation("tex_y");
	unis[1] = program.uniformLocation("tex_u");
	unis[2] = program.uniformLocation("tex_v");

	glGenTextures(3, texs);

	glBindTexture(GL_TEXTURE_2D, texs[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texs[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, texs[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_bInitedGL = true;
}

void VideoRenderWidget::paintGL()
{
	std::lock_guard<std::mutex> lk(m_pData->m_mutex);

	auto &m_width = m_pData->m_width;
	auto &m_height = m_pData->m_height;
	auto &m_datas = m_pData->m_datas;
	auto &m_len = m_pData->m_len;
	auto &texs = m_pData->texs;
	auto &unis = m_pData->unis;

	if (nullptr == m_datas
		|| m_width <= 0
		|| m_height <= 0)
	{
		return;
	}

	unsigned char *dataY = m_datas;
	unsigned char *dataU = dataY + (m_width * m_height);
	unsigned char *dataV = dataU + (m_width * m_height / 4);

	int widths[] = { m_width, m_width / 2, m_width / 2 };
	int heights[] = { m_height, m_height / 2, m_height / 2 };
	unsigned char *datas[] = { dataY, dataU, dataV };

	for (int i = 0; i < _countof(widths); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, texs[i]);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, widths[i], heights[i], GL_RED, GL_UNSIGNED_BYTE, datas[i]);
		glUniform1i(unis[i], i);
	}

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool VideoRenderWidget::event(QEvent * event)
{
	if (event->type() == m_pData->evnetId)
	{
		std::lock_guard<std::mutex> lk(m_pData->m_mutex);
		innerInit();
	}
	return __super::event(event);
}

void VideoRenderWidget::innerInit()
{
	auto &m_width = m_pData->m_width;
	auto &m_height = m_pData->m_height;
	auto &texs = m_pData->texs;

	if (!m_pData->m_bInitedGL)
	{
		assert(false);
		return;
	}
	glBindTexture(GL_TEXTURE_2D, texs[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glBindTexture(GL_TEXTURE_2D, texs[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width / 2, m_height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glBindTexture(GL_TEXTURE_2D, texs[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width / 2, m_height / 2, 0, GL_RED, GL_UNSIGNED_BYTE, 0);
}
