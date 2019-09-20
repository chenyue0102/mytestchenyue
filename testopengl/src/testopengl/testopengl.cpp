// testopengl.cpp : �������̨Ӧ�ó������ڵ㡣
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
	glBegin(GL_LINE_STRIP);//���һ�������һ���㲻����
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
	glBegin(GL_LINE_LOOP);//���һ�������һ��������
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // ������������Ի�x��
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // ������������Ի�y��
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
	glPolygonMode(GL_FRONT, GL_FILL);//����Ϊ���
	glPolygonMode(GL_BACK, GL_LINE);//����Ϊ��Ե����
	//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);//˫��Ϊ�������
	//һ����ʱ��˳��Ϊ����
	glFrontFace(GL_CCW);//������ʱ��Ϊ���棬Counter Clock Wise
	//glFrontFace(GL_CW);//����˳ʱ��Ϊ����
	//��ʱ�����һ��������
	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, -0.5f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	//˳֮�����һ��������
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
	//����xyƽ��
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
	//������Ȳ��ԣ�����Ƶģ��ں�������岻���ڵ�ǰ�������
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//����ͶӰ����
	glMatrixMode(GL_PROJECTION);
	//��ǰ��������Ϊ��λ����
	glLoadIdentity();
	//���ÿ��ӿռ�,�ӽ�Ϊ75�ȣ��߿��Ϊ1.0��������Ӿ���Ϊ1.��Զ���Ӿ���Ϊ400000000
	gluPerspective(75, 1, 1, maxFar);
	//���õ�ǰ�����ľ���Ϊ��ģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	int div = 1;
	//�ı�۲���λ��,ǰ����������ʾ�˹۲���λ�ã��м�����������ʾ�˹۲�Ŀ���λ�ã�����������������(0,0,0)�� (x,y,z)��ֱ�ߣ�����ʾ�˹۲�����Ϊ�ġ��ϡ�����
	gluLookAt(200000000 / div / 10, -200000000/ div, 200000000/ div, 0, 0, 0, 0, 0, 1);

	drawBackline();

	//����̫��
	glColor3f(1.0f, 0.0f, 0.0f);
	//��һ��������ʾ����İ뾶�����������������ˡ��桱����Ŀ
	glutWireTeapot(69600000);
	//glutSolidSphere(69600000, 20, 20);
	
	// ������ɫ�ġ�����
	glColor3f(0.0f, 0.0f, 1.0f);
	glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, -1.0f);
	//glRotatef(day , 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, 1.0f);
	//glutSolidSphere(15945000, 20, 20);
	glutWireTeapot(15945000);

	// ���ƻ�ɫ�ġ�������
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
	//���
	//glPointSize(5.0f);
	//�߿�
	//glLineWidth(1.0f);
	//��������
	//glEnable(GL_LINE_STIPPLE);
	//�����ߵ����ؼ�������ߵ�ļ��
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
	glutCreateWindow("OpenGL ����");
	glutDisplayFunc(&myDisplay);
	glutIdleFunc(&myIdle);
	glutMainLoop();
    return 0;
}

