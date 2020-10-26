// testspine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
#include <thread>
#include "rendercmdscache.h"
//#include "spineitem.h"
RenderCmdsCache *g_RenderCmdsCache = 0;
SpineItem *g_SpineItem = 0;

void init() {
	g_RenderCmdsCache = new RenderCmdsCache();
	//g_SpineItem = new SpineItem();
	//g_SpineItem->setAtlasFile("../../../android/testspine/app/src/main/assets/alien.atlas");
	//g_SpineItem->setSkeletonFile("../../../android/testspine/app/src/main/assets/alien-ess.json");
}

void testdraw() {
	//g_SpineItem->render()
}

void myIdle() {
	testdraw();
	std::this_thread::sleep_for(std::chrono::microseconds(1));
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
    std::cout << "Hello World!\n";

	init();

	glutDisplayFunc(&testdraw);
	glutIdleFunc(&myIdle);
	//glutKeyboardFunc(&keyboard);
	//glutSpecialFunc(&specialkey);
	glutMainLoop();
}
