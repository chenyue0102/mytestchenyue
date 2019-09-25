// testopengl.cpp : �������̨Ӧ�ó������ڵ㡣
//
#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <math.h>
#include <time.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>

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
	//gluLookAt(200000000 / div / 10, -200000000/ div, 200000000/ div, 0, 0, 0, 0, 0, 1);
	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	drawBackline();

	//����̫��
	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
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
	// ����̫���Ĳ��ʲ�����̫��
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
	//��һ��������ʾ����İ뾶�����������������ˡ��桱����Ŀ
	//glutWireTeapot(69600000);
	//glutSolidSphere(69600000, 20, 20);
	
	// �������Ĳ��ʲ����Ƶ���
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

	// ������ɫ�ġ�����
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, -1.0f);
	//glRotatef(day , 0.0f, 0.0f, -1.0f);
	//glTranslatef(150000000, 0.0f, 0.0f);
	//glRotatef(day / 30.0 * 360.0, 0.0f, 0.0f, 1.0f);
	//glutSolidSphere(15945000, 20, 20);
	//glutWireTeapot(15945000);

	// ���ƻ�ɫ�ġ�������
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
	selectFont(FONT_SIZE, DEFAULT_CHARSET, L"΢���ź�");
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
		wglUseFontBitmapsW(wglGetCurrentDC(), L'��', 1, lists + 1);
		wglUseFontBitmapsW(wglGetCurrentDC(), L'��', 1, lists + 2);
	}
	glColor3f(0.0f, 0.0f, 1.0f);
	glRasterPos2f(x, y);
	for (int i = 0; i < 10; i++)
	{
		glCallList(lists + i);
	}
	//charToTexture(L'��');
	glFlush();
	//glDeleteLists(lists, 10);
}

void drawTextTexture()
{
	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����ӽ�
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);*/

	static GLuint tex = charToTexture(L'��');
	
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
	//drawSun();
	//drawIndex();
	//drawText(-1.0f, 0.0f);
	drawTextTexture();
}

void myIdle()
{
	static DWORD t = 0;
	DWORD tCur = GetTickCount();
	if (tCur - t > 30)
	{
		t = tCur;
		++day;
		if (day >= 360)
			day = 0;
		//myDisplay();
		float x = float(day) / 360 * 2 - 1.0f;
		drawText(x, 0.0f);
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL ����");
	auto v = glGetString(GL_VERSION);
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	printf("OpenGL Version=%s texturemaxsize=%d", v, max);
	glutDisplayFunc(&myDisplay);
	//glutIdleFunc(&myIdle);
	glutMainLoop();
    return 0;
}

