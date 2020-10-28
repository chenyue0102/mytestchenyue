// testspine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <assert.h>
#include <GL/glew.h>
#include "GL/glut.h"
#include <GL/freeglut_ext.h>
#include <thread>
#include "rendercmdscache.h"
#include "spineitem.h"
RenderCmdsCache *g_RenderCmdsCache = 0;
SpineItem *g_SpineItem = 0;

void init() {
	g_RenderCmdsCache = new RenderCmdsCache();
	g_RenderCmdsCache->initShaderProgram();

	g_SpineItem = new SpineItem();
	g_SpineItem->setAtlasFile("../../../android/testspine/app/src/main/assets/alien.atlas");
	g_SpineItem->setSkeletonFile("../../../android/testspine/app/src/main/assets/alien-ess.json");
	g_SpineItem->create();
	g_SpineItem->setAnimation(0, "death", false);
	g_SpineItem->setSkin("default");
}

void testdraw() {
	g_SpineItem->updateSkeletonAnimation();
	g_SpineItem->batchRenderCmd(g_RenderCmdsCache);
	g_SpineItem->renderToCache(g_RenderCmdsCache);
	g_RenderCmdsCache->render();
	glFlush();
}

void myIdle() {
	testdraw();
	std::this_thread::sleep_for(std::chrono::microseconds(20));
}

void GLAPIENTRY DEBUGPROC(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	static bool b = false;
	if (b) {
		printf("%s", message);
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
	printf("OpenGL Version=%s texturemaxsize=%d\n", v, max);

	glEnable(GL_DEBUG_OUTPUT);
	

	GLint flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
	{
		printf("debug print init ok\n");
	}

	//初始化 glew wglMakeCurrent
	GLenum status = glewInit();
	assert(GLEW_OK == status);
    std::cout << "Hello World!\n";

	glDebugMessageCallback(&DEBUGPROC, 0);

	

	init();

	glutDisplayFunc(&testdraw);
	glutIdleFunc(&myIdle);
	//glutKeyboardFunc(&keyboard);
	//glutSpecialFunc(&specialkey);
	glutMainLoop();
}
