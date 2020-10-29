#include "MyTexture.h"
#ifdef WIN32
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <windows.h>
#else
#include <OpenGLES/ES3/gl.h>
#endif
#include "OpenGLESHelper.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include"stb_image.h"



MyTexture::MyTexture(const char *fileName)
	: mFileName(fileName)
	, mTexture(0)
{

}

MyTexture::~MyTexture() {

}

void MyTexture::bind() {
	if (0 == mTexture) {
		int width = 0, height = 0, channel = 0;
		stbi_uc *buffer = stbi_load(mFileName.c_str(), &width, &height, &channel, 0);

		glGenTextures(1, &mTexture); CHECKERR();
		glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1); CHECKERR();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width,
			height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			buffer); CHECKERR();
		
		STBI_FREE(buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); CHECKERR();
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); CHECKERR();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); CHECKERR();
		glGenerateMipmap(GL_TEXTURE_2D); CHECKERR();
	}
	CHECKERR();
	glBindTexture(GL_TEXTURE_2D, mTexture); CHECKERR();
}
