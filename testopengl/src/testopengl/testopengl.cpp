// testopengl.cpp : 定义控制台应用程序的入口点。
//
#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include "GL/glut.h"

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
	gluLookAt(200000000 / div / 10, -200000000/ div, 200000000/ div, 0, 0, 0, 0, 0, 1);

	drawBackline();

	//绘制太阳
	glColor3f(1.0f, 0.0f, 0.0f);
	//第一个参数表示球体的半径，后两个参数代表了“面”的数目
	glutWireTeapot(69600000);
	//glutSolidSphere(69600000, 20, 20);
	
	// 绘制蓝色的“地球”
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, -1.0f);
	//glRotatef(day , 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, 1.0f);
	//glutSolidSphere(15945000, 20, 20);
	glutWireTeapot(15945000);

	// 绘制黄色的“月亮”
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	//glutSolidSphere(4345000, 20, 20);

	glutSwapBuffers();
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
	drawSun();
}

void myIdle()
{
	static DWORD t = 0;
	DWORD tCur = GetTickCount();
	if (tCur - t > 300)
	{
		t = tCur;
		++day;
		if (day >= 360)
			day = 0;
		myDisplay();
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL 程序");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
    return 0;
}

