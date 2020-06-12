// testopengl.cpp : 定义控制台应用程序的入口点。
//
#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <assert.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
#include "vmath.h"

void CHECKERR() {
	int err = 0; 
	if (GL_NO_ERROR != (err = glGetError()))
	{
		printf("glGetError=%d\n", err);
	}
}

void drawPoints()
{
	glBegin(GL_POINTS);
	{
		//glVertex2f(0.0f, 0.0f);
		glVertex2f(0.5f, 0.0f);
		glVertex2d(-1, -1);
		glVertex2d(0, 0);
	}
	glEnd();
}

void drawLines()
{
	glBegin(GL_LINE_STRIP);//最后一个点与第一个点不连接
	{
		glVertex2d(0, 0);
		glVertex2d(1, 1);
		glVertex2f(-0.9, 0.8);
	}
	glEnd();

	glBegin(GL_POLYGON);
	int n = 50;
	for (int i = 0; i < n; i++)
	{
		const float R = 0.5f;
		glVertex2f(R*cos(2 * M_PI / n*i), R*sin(2 * M_PI / n*i));
	}
	glEnd();

	GLfloat a = 1 / (2 - 2 * cos(72 * M_PI / 180));
	GLfloat bx = a * cos(18 * M_PI / 180);
	GLfloat by = a * sin(18 * M_PI / 180);
	GLfloat cy = -a * cos(18 * M_PI / 180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { 0.5, cy },
		PointD[2] = { -0.5, cy },
		PointE[2] = { -bx, by };
	glBegin(GL_LINE_LOOP);//最后一个点与第一个点连接
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
	glEnd();
	glBegin(GL_LINE_STRIP);
	const GLfloat factor = 0.1f;
	for (auto x = -1.0f / factor; x<1.0f / factor; x += 0.01f)
	{
		glVertex2f(x*factor, sin(x)*factor);
	}
	glEnd();
}

void drawPolygon()
{
	glPolygonMode(GL_FRONT, GL_FILL);//正面为填充
	glPolygonMode(GL_BACK, GL_LINE);//反面为边缘绘制
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//双面为顶点绘制
	//一半逆时针顺序为正面
	glFrontFace(GL_CCW);//设置逆时针为正面，Counter Clock Wise
	//glFrontFace(GL_CW);//设置顺时针为正面
	//逆时针绘制一个正方形
	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, -0.5f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	//顺之阵绘制一个正方形
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glEnd();
}

void testShadModel()
{
	glShadeModel(GL_SMOOTH);
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex2f(1.0f, 1.0f);
	glEnd();
}
int day = 0;
int maxFar = 400000000;
void drawBackline()
{
	int maxLineCount = 20;
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	//绘制xy平面
	for (int i = 0; i < maxLineCount; i++)
	{
		int yStep = maxFar / maxLineCount * 2;
		glVertex3f(-maxFar, -maxFar + yStep * i, 0.0f);
		glVertex3f(maxFar, -maxFar + yStep * i, 0.0f);

		glVertex3f(-maxFar + yStep * i, -maxFar, 0.0f);
		glVertex3f(-maxFar + yStep * i, maxFar, 0.0f);
	}
	glEnd();

	glLineWidth(4);
	glColor3f(1.0f, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(maxFar / 2, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, maxFar / 2, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, maxFar / 2);
	glEnd();
	glLineWidth(1);
}

void drawSun()
{
	//启用深度测试，后绘制的，在后面的物体不会遮挡前面的物体
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//启用投影矩阵
	glMatrixMode(GL_PROJECTION);
	//当前矩阵设置为单位矩阵
	glLoadIdentity();
	//设置可视空间,视角为75度，高宽比为1.0。最近可视距离为1.最远可视距离为400000000
	gluPerspective(75, 1, 1, maxFar);
	//设置当前操作的矩阵为“模型视图矩阵”
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int div = 1;
	//改变观察点的位置,前三个参数表示了观察点的位置，中间三个参数表示了观察目标的位置，最后三个参数代表从(0,0,0)到 (x,y,z)的直线，它表示了观察者认为的“上”方向
	//gluLookAt(200000000 / div / 10, -200000000/ div, 200000000/ div, 0, 0, 0, 0, 0, 1);
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	drawBackline();

	//绘制太阳
	// 定义太阳光源，它是一种白色的光源
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}
	// 定义太阳的材质并绘制太阳
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(2.0, 40, 32);
	}

	//glColor3f(1.0f, 0.0f, 0.0f);
	//第一个参数表示球体的半径，后两个参数代表了“面”的数目
	//glutWireTeapot(69600000);
	//glutSolidSphere(69600000, 20, 20);
	
	// 定义地球的材质并绘制地球
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(0.0f, 0.0f, -1.0f, 0.0f);
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
	}

	// 绘制蓝色的“地球”
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, -1.0f);
	//glRotatef(day , 0.0f, 0.0f, -1.0f);
	//glTranslatef(150000000, 0.0f, 0.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, 1.0f);
	//glutSolidSphere(15945000, 20, 20);
	//glutWireTeapot(15945000);

	// 绘制黄色的“月亮”
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	//glTranslatef(38000000, 0.0f, 0.0f);
	//glutSolidSphere(4345000, 20, 20);

	glutSwapBuffers();
}

void drawIndex()
{
	glClear(GL_COLOR_BUFFER_BIT);
	static const GLfloat vertex_list[][2] = 
	{
		-0.5f, -0.5f,
		-0.5f, 0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f,
	};
	static const GLint index_list[] = 
	{
		0, 1, 2, 3,
	};
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertex_list);
	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, index_list);

	glFlush();
}

void selectFont(int size, int charset, const wchar_t* face) {
	HFONT hFont = CreateFontW(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

#define FONT_SIZE       64
#define TEXTURE_SIZE    FONT_SIZE

GLuint charToTexture(const wchar_t ch)
{
	HDC hdc = wglGetCurrentDC();
	selectFont(FONT_SIZE, DEFAULT_CHARSET, L"微软雅黑");
	int w = 0, x = 0, y = 0;
	GetCharWidth32W(hdc, ch, ch, &w);
	typedef void (APIENTRY*PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
	PFNGLWINDOWPOS2IPROC glWindowPos2i = (PFNGLWINDOWPOS2IPROC)glutGetProcAddress("glWindowPos2i");
	x = (TEXTURE_SIZE - w) / 2;
	y = FONT_SIZE / 8;
	glWindowPos2i(x, y);

	GLuint list = glGenLists(1);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_FOG);
	glDisable(GL_TEXTURE_2D);

	wglUseFontBitmapsW(hdc, ch, 1, list);
	glCallList(list);
	glDeleteLists(list, 1);

	GLuint texid = 0;
	glGenTextures(1, &texid);
	glBindTexture(GL_TEXTURE_2D, texid);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE4, 0, 0, TEXTURE_SIZE, TEXTURE_SIZE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return texid;
}

void drawText(float x, float y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	static GLuint lists = 0;
	if (0 == lists)
	{
		lists = glGenLists(10);
		wglUseFontBitmapsW(wglGetCurrentDC(), L'0', 10, lists);
		wglUseFontBitmapsW(wglGetCurrentDC(), L'你', 1, lists + 1);
		wglUseFontBitmapsW(wglGetCurrentDC(), L'好', 1, lists + 2);
	}
	glColor3f(0.0f, 0.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < 10; i++)
	{
		glCallList(lists + i);
	}
	//charToTexture(L'你');
	glFlush();
	//glDeleteLists(lists, 10);
}

void drawTextTexture()
{
	// 清除屏幕
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 设置视角
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);*/

	static GLuint tex = charToTexture(L'你');
	
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex);
	GLfloat color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);

	glBegin(GL_QUADS);
	int size = 1;
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, size); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(size, size); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(size, 0.0f); glVertex2f(1.0f, -1.0f);
	glEnd();
	glFlush();
}

static GLuint g_texture = 0;
static GLuint g_depthBuffer = 0;
static GLuint g_frameBuffer = 0;
const int TEXTURE_WIDTH = 1024;
const int TEXTURE_HEIGHT = 768;
char *g_dataBuffer = 0;

void initTexture()
{
	g_dataBuffer = new char[TEXTURE_WIDTH * TEXTURE_HEIGHT * 3];
	//创建纹理
	glGenTextures(1, &g_texture);
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//创建深度缓冲
	glGenRenderbuffers(1, &g_depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, g_depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, TEXTURE_WIDTH, TEXTURE_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//创建FBO对象
	glGenFramebuffers(1, &g_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_texture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_depthBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	assert(GL_FRAMEBUFFER_COMPLETE == status);
}

void renderToTexture()
{
	//取消绑定
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, g_frameBuffer);
	glViewport(0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT);

	//render
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawLines();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


bool SaveBitmap(const char *pFileName, int width, int height, int biBitCount, const void *pBuf, int nBufLen)
{
	if (nullptr == pFileName
		|| 0 == width
		|| 0 == height
		|| !(biBitCount == 24 || biBitCount == 32 || biBitCount == 16)
		|| nullptr == pBuf
		|| nBufLen < ((width * height * biBitCount) / 8)
		)
	{
		return false;
	}
	else
	{
		BITMAPFILEHEADER bfh = { 0 };
		bfh.bfType = 'MB';
		bfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + nBufLen;
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		FILE *fp = fopen(pFileName, "wb");
		fwrite(&bfh, 1, sizeof(bfh), fp);
		BITMAPINFOHEADER bih = { 0 };
		bih.biSize = sizeof(bih);
		bih.biWidth = width;
		bih.biHeight = height;
		bih.biPlanes = 1;
		bih.biBitCount = biBitCount;
		fwrite(&bih, 1, sizeof(bih), fp);
		fwrite(pBuf, 1, nBufLen, fp);
		fclose(fp);
		return true;
	}
}
void drawFrameBufferObject()
{
	if (0 == g_texture)
	{
		initTexture();
	}
	renderToTexture();

	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, g_texture);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, g_dataBuffer);
		glDisable(GL_TEXTURE_2D);
		SaveBitmap("d:/1.bmp", TEXTURE_WIDTH, TEXTURE_HEIGHT, 24, g_dataBuffer, TEXTURE_WIDTH * TEXTURE_HEIGHT * 3);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glViewport(0, 0, 400, 400);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);

	glBegin(GL_QUADS);
	int size = 1;
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, size); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(size, size); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(size, 0.0f); glVertex2f(1.0f, -1.0f);
	glEnd();
	glFlush();
}

void drawImage() {

}

void myDisplay()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	//点宽
	//glPointSize(5.0f);
	//线宽
	//glLineWidth(1.0f);
	//启用虚线
	//glEnable(GL_LINE_STIPPLE);
	//画虚线的像素间隔和虚线点的间隔
	//glLineStipple(1, 0b0101010101011111);
	//glColor3f(0.0f, 1.0f, 1.0f);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	//drawPoints();
	//drawLines();
	//drawPolygon();
	//testShadModel();
	//drawSun();
	//drawIndex();
	//drawText(-1.0f, 0.0f);
	//drawTextTexture();

	//drawFrameBufferObject();
	drawImage();
}

//void myIdle()
//{
//	static DWORD t = 0;
//	DWORD tCur = GetTickCount();
//	if (tCur - t > 300)
//	{
//		t = tCur;
//		++day;
//		if (day >= 360)
//			day = 0;
//		//myDisplay();
//		float x = float(day) / 360 * 2 - 1.0f;
//		drawText(x, 0.0f);
//	}
//}


inline void outputCompileShader(GLuint shader)
{
	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (GL_FALSE == status || true)
	{
		const int MAX_LOG_LENGTH = 512;
		GLint len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		if (len < MAX_LOG_LENGTH)
		{
			GLchar szBuf[MAX_LOG_LENGTH] = { 0 };
			int len = MAX_LOG_LENGTH;
			glGetShaderInfoLog(shader, MAX_LOG_LENGTH, nullptr, szBuf);
			printf("%s\n", szBuf);
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, nullptr, buf);
			buf[len] = '\0';
			printf("%s\n", buf);
			delete[]buf;
		}
		assert(GL_FALSE != status);
	}
}
inline void outputProgramLog(GLuint program)
{
	GLint status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (GL_FALSE == status)
	{
		const int MAX_LOG_LENGTH = 512;
		GLint len = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
		if (len < MAX_LOG_LENGTH)
		{
			GLchar szBuf[MAX_LOG_LENGTH] = { 0 };
			glGetProgramInfoLog(program, MAX_LOG_LENGTH, nullptr, szBuf);
			printf("%s\n", szBuf);
		}
		else
		{
			GLchar *buf = new GLchar[len + 1];
			glGetProgramInfoLog(program, len, nullptr, buf);
			buf[len] = '\0';
			printf("%s\n", buf);
			delete[]buf;
		}
		assert(false);
	}
}

#include "glsl.h"
#define BUFFER_OFFSET(offset) ((void*)(offset))
GLuint g_vIndex = 0;
GLuint g_bIndex = 0, g_ebIndex = 0;
GLuint g_program = 0;
GLuint g_pipeline = 0;
GLuint g_vprogram = 0, g_fprogram = 0;

//#define USE_UCHAR_COLOR

//初始化顶点数组
GLfloat g_vPoints[][4] = {
	-1.0f, -1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f, 1.0f,
};
#ifdef USE_UCHAR_COLOR
//使用unsigned char 类型值
GLbyte g_colors[][4] = {
	{ 255, 0, 0， 255 },
	{ 0, 255, 0， 255 },
	{ 0, 0, 255， 255 },
};
#else
GLfloat g_colors[][4] = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 1.0f, 1.0f, 1.0f,
	0.5f, 0.0f, 0.0f, 1.0f,
	0.0f, 0.5f, 0.0f, 1.0f,
};

GLushort g_indices[] = { 
	0, 1, 2, 3, 6, 7, 4, 5,
	0xFFFF,
	2, 6, 0, 4,1, 5, 3, 7};//元素索引
void initBufferArray() 
{
#endif
	glGenBuffers(1, &g_bIndex);//生成1个buffer对象
	glBindBuffer(GL_ARRAY_BUFFER, g_bIndex);//激活buffer对象
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vPoints) + sizeof(g_colors), nullptr, GL_STATIC_DRAW);//分配空间

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(g_vPoints), g_vPoints);//设置顶点坐标缓存
	
#if 0
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(g_vPoints), sizeof(g_colors), g_colors);//设置顶点颜色缓存
#endif
#if 1
	//也可以使用map形式设置
	GLboolean isOk = GL_FALSE;
	if (false) {
		void* mapBuf = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		memcpy((char*)mapBuf + sizeof(g_vPoints), g_colors, sizeof(g_colors));
		isOk = glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	else {
		//map range,GL_MAP_FLUSH_EXPLICIT_BIT:应用程序主动通知刷新区域
		void* mapBuf = glMapBufferRange(GL_ARRAY_BUFFER, sizeof(g_vPoints), sizeof(g_colors), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);
		memcpy(mapBuf, g_colors, sizeof(g_colors));
		glFlushMappedBufferRange(GL_ARRAY_BUFFER, 0, sizeof(g_colors));
		isOk = glUnmapBuffer(GL_ARRAY_BUFFER);
	}
#endif
	//GLfloat checkPoints[3 * 4 + 3 * 4] = { 0.0 };
	//glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vPoints) + sizeof(colors), checkPoints);//获取缓冲数据

	
	GLuint buf = GL_INVALID_INDEX;
	glGenBuffers(1, &g_ebIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_indices), g_indices, GL_STATIC_DRAW);
	//glDeleteBuffers(1, &buf);
	if (false) {
		//丢弃缓存数据
		glInvalidateBufferData(g_bIndex);
	}
}


void initVertex() 
{
	glGenVertexArrays(1, &g_vIndex);//分配1个顶点数组对象
	glBindVertexArray(g_vIndex);//激活第一个顶点数组对象
	glBindBuffer(GL_ARRAY_BUFFER, g_bIndex);//使用g_bIndex
	GLuint vertexIn = 1;//顶点着色器中vPosition的位置index, 可以通过glGetAttribLocation(m_program, "vPosition");获取
	GLint perVertexPointCount = 4;//一个顶点的坐标数量，如：xyz,则是3
	GLsizei stride = 0;//连续顶点之间的偏移量
	GLboolean normalized = GL_FALSE;
	int offset = 0;// sizeof(GLfloat) * 2;//从第二个顶点坐标开始
	glVertexAttribPointer(vertexIn, perVertexPointCount, GL_FLOAT, normalized, stride, BUFFER_OFFSET(offset));//指定顶点属性的数据格式和位置
	glEnableVertexAttribArray(vertexIn);//启用顶点

	GLuint tVertexIn = 2;
	glVertexAttribPointer(tVertexIn, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(g_vPoints)));//指定颜色顶点的偏移
	glEnableVertexAttribArray(tVertexIn);//启用顶点
}
#define USE_PIPELINE

#ifdef USE_PIPELINE
void initProgram()
{
	g_vprogram = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &vString);
	g_fprogram = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &fString);
	glGenProgramPipelines(1, &g_pipeline);
}
#else
void initProgram()
{
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vShader, 1, &vString, nullptr);
	glShaderSource(fShader, 1, &fString, nullptr);

	glCompileShader(vShader);
	outputCompileShader(vShader);
	glCompileShader(fShader);
	outputCompileShader(fShader);
	CHECKERR();

	g_program = glCreateProgram();

	glAttachShader(g_program, vShader);
	CHECKERR();
	glAttachShader(g_program, fShader);
	CHECKERR();

	glLinkProgram(g_program);
	outputProgramLog(g_program);

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	glUseProgram(g_program);
}
#endif

size_t TypeSize(GLenum type)
{
	size_t size = 0;
#define CASE(Enum, Count, Type) \
case Enum:size = Count * sizeof(Type);break;
	switch (type) {
		CASE(GL_FLOAT,				1, GLfloat);
		CASE(GL_FLOAT_VEC2,			2, GLfloat);
		CASE(GL_FLOAT_VEC3,			3, GLfloat);
		CASE(GL_FLOAT_VEC4,			4, GLfloat);
		CASE(GL_INT,				1, GLint);
		CASE(GL_INT_VEC2,			2, GLint);
		CASE(GL_INT_VEC3,			3, GLint);
		CASE(GL_INT_VEC4,			4, GLint);
		CASE(GL_UNSIGNED_INT,		1, GLuint);
		CASE(GL_UNSIGNED_INT_VEC2,	2, GLuint);
		CASE(GL_UNSIGNED_INT_VEC3,	3, GLuint);
		CASE(GL_UNSIGNED_INT_VEC4,	4, GLuint);
		CASE(GL_BOOL, 				1, GLboolean);
		CASE(GL_BOOL_VEC2,			2, GLboolean);
		CASE(GL_BOOL_VEC3,			3, GLboolean);
		CASE(GL_BOOL_VEC4,			4, GLboolean);
		CASE(GL_FLOAT_MAT2, 		4, GLfloat);
		CASE(GL_FLOAT_MAT2x3,		6, GLfloat);
		CASE(GL_FLOAT_MAT2x4,		8, GLfloat);
		CASE(GL_FLOAT_MAT3,			9, GLfloat);
		CASE(GL_FLOAT_MAT3x2,		6, GLfloat);
		CASE(GL_FLOAT_MAT3x4,		12, GLfloat);
		CASE(GL_FLOAT_MAT4,			16, GLfloat);
		CASE(GL_FLOAT_MAT4x2,		8, GLfloat);
		CASE(GL_FLOAT_MAT4x3,		12, GLfloat);
#undef CASE
	default:
		printf("unknown type:%d\n", type);
		break;
	}

	return size;
}

void initUniform(GLuint program)
{
	GLint myMatrix = glGetUniformLocation(program, "myMatrix");//获取translationMatrix的位置
	CHECKERR();
	//glProgramUniform3f(program, myLocation, 0.3, 0.6, 1.0);
#if 1
	static int i = 500;
	i += 30;
	float t = float(i & 0x1FFF) / float(0x1FFF);
	static float q = 0.0f;
	static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
	static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
	static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

	vmath::mat4 translateMatrix = vmath::translate(1.0f, 0.0f, 0.0f);//移动
	vmath::mat4 scaleMatrix = vmath::scale(0.4f, 0.8f, 1.0f);
	vmath::mat4 rotateMatrix = vmath::rotate(0.0f, 0.0f, 90.0f);//旋转
	vmath::mat4 standardMatrix = vmath::mat4(
		vmath::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vmath::vec4(0.0f, 1.0f, 0.0f, 0.0f),
		vmath::vec4(0.0f, 0.0f, 1.0f, 0.0f),
		vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	//translateMatrix * rotateMatrix，先旋转，后平移
	float aspect = 1.0f; //height/width
	vmath::mat4 model_matrix(vmath::translate(0.0f, 0.0f, -5.0f) * vmath::rotate(t * 360.0f, Y) * vmath::rotate(t * 720.0f, Z));
	vmath::mat4 projection_matrix(vmath::frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 500.0f));
	vmath::mat4 matrix = projection_matrix * model_matrix;
#else
	GLfloat matrix[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0, 
		0.0, 0.0, 1.0, 0.0, 
		0.5, 0.0, 0.0, 1.0,
	};
#endif
	glProgramUniformMatrix4fv(program, myMatrix, 1, GL_FALSE, matrix);//使用glUniformMatrix4fv，必须先glUseProgram(program)
	CHECKERR();
	
	//获取uniform 块索引
	GLuint blockIndex = glGetUniformBlockIndex(program, "MyTest");

	//获取uniform块大小
	GLint uboSize = 0;
	glGetActiveUniformBlockiv(program, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);
	//分配缓冲区
	GLvoid* buffer = malloc(uboSize);
	memset(buffer, 0, uboSize);

	const int NUM = 2;
	const char* ppNames[NUM] = { "isReverse", "isGradual" };
	GLuint itemIndexs[NUM] = { GL_INVALID_INDEX, GL_INVALID_INDEX };
	GLint size[NUM];
	GLint offset[NUM];
	GLint type[NUM];
	//获取每个item的index
	glGetUniformIndices(program, 2, ppNames, itemIndexs);
	//获取item的大小
	glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_SIZE, size);
	//获取item的缓冲区偏移
	glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_OFFSET, offset);
	//获取item类型
	glGetActiveUniformsiv(program, NUM, itemIndexs, GL_UNIFORM_TYPE, type);
	GLboolean values[NUM] = { GL_TRUE, GL_TRUE };
	for (int i = 0; i < NUM; i++)
	{
		memcpy((char*)buffer + offset[i], &values[i], size[i] * TypeSize(type[i]));
	}

	//生成一个UNIFORM buffer
	GLuint ubo = -1;
	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
	//用uniform buffer来为uniform设值
	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, ubo);
	free(buffer);

	glUseProgram(0);
}

//GLuint g_texture = 0;

void init() 
{
	initBufferArray();
	initVertex();
	initProgram();
	
	//glEnable(GL_SAMPLE_SHADING);
	//glMinSampleShading(1.0);

	//启用剪切
	if (false) {
		glEnable(GL_SCISSOR_TEST);
		glScissor(100, 100, 200, 200);
	}

	//启用反走样
	if (false)
	{
		glEnable(GL_POLYGON_SMOOTH);//启用多边形平滑
		glEnable(GL_BLEND);	//启用混合
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	}
	//charToTexture(L"Hello, world");
	
	//设置清除颜色
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

typedef struct DrawArraysIndirectCommand {
	GLuint count;
	GLuint primCount;
	GLuint first;
	GLuint baseInstance;
};

void testdraw() 
{
#ifdef USE_PIPELINE
	initUniform(g_vprogram);
	glUseProgramStages(g_pipeline, GL_VERTEX_SHADER_BIT, g_vprogram);
	glUseProgramStages(g_pipeline, GL_FRAGMENT_SHADER_BIT, g_fprogram);
	glBindProgramPipeline(g_pipeline);
#else
	initUniform(g_program);
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glPointSize(15.0);//只对点生效
	glLineWidth(15.0);//只对线生效

	glBindVertexArray(g_vIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_ebIndex);

	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);

	int drawType = 1;
	switch (drawType) {
	case 0:
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	break;
	case 1: {
		//如果有变量bind到GL_ELEMENT_ARRAY_BUFFER，则indices是offset bytes 缓冲区
		//否则是pointer to indices
#if 0
		if (0) {
			glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(sizeof(GLushort) * 1));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else {
			glDrawElements(GL_LINES, 4, GL_UNSIGNED_SHORT, g_indices);
		}
#endif
		glDrawElements(GL_TRIANGLE_STRIP, 17, GL_UNSIGNED_SHORT, 0);
	}
	break;
	case 2: {
		GLint basevertex = 1;
		//与glDrawElements类似，元素index为indices[i + basevertex];
		glDrawElementsBaseVertex(GL_LINES, 4, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0), basevertex);
	}
	break;
	case 3: {
		//glDrawRangeElements(GL_LINES, 3, 4, 2, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
	}break;
	case 4: {
		//绘制primcount次，GLSL中gl_InstanceID会依次递增
		GLsizei primcount = 4;
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 3, primcount);
	}break;
	case 5: {
		DrawArraysIndirectCommand cmd;
		cmd.count = 4;
		cmd.first = 1;
		cmd.primCount = 4;
		cmd.baseInstance = 0;
		GLuint buf;
		glGenBuffers(1, &buf);
		glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buf);
		glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(cmd), &cmd, GL_STATIC_DRAW);
		glDrawArraysIndirect(GL_LINES, BUFFER_OFFSET(0));
		glDeleteBuffers(1, &buf);
	}break;
	case 6: {
		GLint firsts[] = { 0, 2 };
		GLint counts[] = { 3, 3 };
		GLsizei drawcount = _countof(firsts);
		glMultiDrawArrays(GL_LINE_STRIP, firsts, counts, drawcount);
	}break;
	default:
		break;
	}
	
	
	//glDrawArrays(GL_LINE_LOOP, 0, 4);
	glFlush();//将命令提交给OpenGL服务器
	//glFinish();//等待OpenGL完成

}

void myIdle() {
	static DWORD t = 0;
	DWORD tCur = GetTickCount();
	if (tCur - t > 30)
	{
		t = tCur;
		testdraw();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("OpenGL 程序");
	auto v = glGetString(GL_VERSION);
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	printf("OpenGL Version=%s texturemaxsize=%d", v, max);
	
	//初始化 glew wglMakeCurrent
	GLenum status = glewInit();
	assert(GLEW_OK == status);

	init();

	glutDisplayFunc(&testdraw);
	glutIdleFunc(&myIdle);
	glutMainLoop();
    return 0;
}

