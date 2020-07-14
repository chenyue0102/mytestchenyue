// testopengl.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include <assert.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
#include "vmath.h"
#include "OpenGLHelper.h"


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
		glVertex2f(-0.9f, 0.8f);
	}
	glEnd();

	glBegin(GL_POLYGON);
	int n = 50;
	for (int i = 0; i < n; i++)
	{
		const float R = 0.5f;
		glVertex2f((GLfloat)(R*cos(2 * M_PI / n*i)), (GLfloat)(R*sin(2 * M_PI / n*i)));
	}
	glEnd();

	GLfloat a = (GLfloat)(1 / (2 - 2 * cos(72 * M_PI / 180)));
	GLfloat bx = (GLfloat)(a * cos(18 * M_PI / 180));
	GLfloat by = (GLfloat)(a * sin(18 * M_PI / 180));
	GLfloat cy = (GLfloat)(-a * cos(18 * M_PI / 180));
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
		glVertex2f((GLfloat)(x*factor), (GLfloat)(sin(x)*factor));
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
		glVertex3f((GLfloat)(-maxFar), (GLfloat)(-maxFar + yStep * i), 0.0f);
		glVertex3f((GLfloat)(maxFar), (GLfloat)(-maxFar + yStep * i), 0.0f);

		glVertex3f((GLfloat)(-maxFar + yStep * i), (GLfloat)(-maxFar), 0.0f);
		glVertex3f((GLfloat)(-maxFar + yStep * i), (GLfloat)(maxFar), 0.0f);
	}
	glEnd();

	glLineWidth(4);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f((GLfloat)(maxFar / 2), 0.0f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.0f, (GLfloat)(maxFar / 2), 0.0f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, (GLfloat)(maxFar / 2));
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
	GLfloat size = 1.0f;
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0.0f, size); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(size, size); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(size, 0.0f); glVertex2f(1.0f, -1.0f);
	glEnd();
	glFlush();
}

namespace TestOpenGL {
	static GLuint g_texture = 0;
	static GLuint g_depthBuffer = 0;
	static GLuint g_frameBuffer = 0;
	const int TEXTURE_WIDTH = 1024;
	const int TEXTURE_HEIGHT = 768;
	char* g_dataBuffer = 0;

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


	bool SaveBitmap(const char* pFileName, int width, int height, int biBitCount, const void* pBuf, int nBufLen)
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
			FILE* fp = fopen(pFileName, "wb");
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
		GLfloat size = 1.0f;
		glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
		glTexCoord2f(0.0f, size); glVertex2f(-1.0f, 1.0f);
		glTexCoord2f(size, size); glVertex2f(1.0f, 1.0f);
		glTexCoord2f(size, 0.0f); glVertex2f(1.0f, -1.0f);
		glEnd();
		glFlush();
	}
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
#include "TestTexture.h"
#include "TestStencil.h"
#include "Test.h"
#include "TestFrameBuffer.h"
#include "TestJpeg.h"
#include "TestSkyBox.h"
#include "TestComputer.h"
#include "TestSphere.h"
#include "TestLight.h"
#include "TestSprite.h"
#include "TestGLSL.h"

void testdraw2() {
	glClearColor(0, 0, 0, 1);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	static bool isfirst = true;
	if (isfirst) {
		//isfirst = false;
		TestStencil::testdraw();
	}
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	Test::testdraw();

	glStencilMask(0xff);
	glStencilFunc(GL_ALWAYS, 0, 0xff);

	glFlush();//将命令提交给OpenGL服务器
	//glFinish();//等待OpenGL完成
	glDisable(GL_STENCIL_TEST);
}

void testdraw() {
	TestGLSL::testdraw();
}

void myIdle() {
	testdraw();
	std::this_thread::sleep_for(std::chrono::microseconds(1));
}

void keyboard(unsigned char key, int x, int y) {
	TestLight::onkeyboard(key, x, y);
}

void specialkey(int key, int x, int y) {
	TestLight::onspecialkey(key, x, y);
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
	printf("OpenGL Version=%s texturemaxsize=%d\n", v, max);
	
	//初始化 glew wglMakeCurrent
	GLenum status = glewInit();
	assert(GLEW_OK == status);

	CHECKERR();

	TestComputer::init();
#if 0
	int width = 0, height = 0, channel = 0;
	void* rgb = TestJpeg::loadJpgImage("testimg.jpg", &width, &height, &channel);
	TestComputer::initrgb2yuvtexture(width, height);
	//OpenGLHelper::SaveBitmap("d:/1.bmp", width, height, channel * 8, rgb, jpgBuffer.length());
	std::string data;
	data.resize(width * height + width * height / 2);
	void *yuv = &data[0];
	int datalen = data.length();
	std::chrono::high_resolution_clock::time_point timePoint = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1; i++) {
		TestComputer::rgb2yuv(width, height, rgb, width * height * channel, yuv, datalen);
	}
	auto diff = std::chrono::high_resolution_clock::now() - timePoint;
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);
	printf("100time:%lld\n", ms.count());
	getchar(); return 0;
	FILE *f = fopen("d:/my.yuv", "wb");
	fwrite(data.data(), 1, data.length(), f);
	fclose(f);
	TestJpeg::freeImage(rgb);
#endif
	TestSphere::init();
	TestLight::init();
	TestSkyBox::init();
	TestTexture::init();
	TestStencil::init();
	Test::init();
	TestFrameBuffer::init();
	TestSprite::init();
	TestGLSL::init();
#if 0
	{
		GLuint tex = 0;
		GLsizei width = 0, height = 0;
		TestJpeg::loadJpg2Texture("d:/1.jpg", GL_RGB8, tex, width, height);
		//TestTexture::setWidthHeight(width, height);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		const GLint bgra[] = { GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA };
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, bgra);
		glBindTexture(GL_TEXTURE_2D, 0);
		TestTexture::setTexture(tex);
	}
#endif

	glutDisplayFunc(&testdraw);
	glutIdleFunc(&myIdle);
	glutKeyboardFunc(&keyboard);
	glutSpecialFunc(&specialkey);
	glutMainLoop();
    return 0;
}

