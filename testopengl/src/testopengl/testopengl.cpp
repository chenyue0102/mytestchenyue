// testopengl.cpp : �������̨Ӧ�ó������ڵ㡣
//
#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <math.h>
#include "GL/glut.h"

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(5.0f);
	glLineWidth(1.0f);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0b0101010101011111);
	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	//glBegin(GL_POINTS);
	//{
	//	//glVertex2f(0.0f, 0.0f);
	//	glVertex2f(0.5f, 0.0f);
	//	glVertex2d(-1, -1);
	//	glVertex2d(0, 0);
	//}
	//glEnd();
	//glBegin(GL_LINE_STRIP);//���һ�������һ���㲻����
	//{
	//	glVertex2d(0, 0);
	//	glVertex2d(1, 1);
	//	glVertex2f(-0.9, 0.8);
	//}
	//glEnd();
	/*glBegin(GL_POLYGON);
	int n = 50;
	for (int i = 0; i < n; i++)
	{
		const float R = 0.5f;
		glVertex2f(R*cos(2 * M_PI / n*i), R*sin(2 * M_PI / n*i));
	}
	glEnd();*/

	//GLfloat a = 1 / (2 - 2 * cos(72 * M_PI / 180));
	//GLfloat bx = a * cos(18 * M_PI / 180);
	//GLfloat by = a * sin(18 * M_PI / 180);
	//GLfloat cy = -a * cos(18 * M_PI / 180);
	//GLfloat
	//	PointA[2] = { 0, a },
	//	PointB[2] = { bx, by },
	//	PointC[2] = { 0.5, cy },
	//	PointD[2] = { -0.5, cy },
	//	PointE[2] = { -bx, by };
	//glBegin(GL_LINE_LOOP);//���һ�������һ��������
	//glVertex2fv(PointA);
	//glVertex2fv(PointC);
	//glVertex2fv(PointE);
	//glVertex2fv(PointB);
	//glVertex2fv(PointD);
	//glEnd();

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
	glFlush();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL ����");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
    return 0;
}

