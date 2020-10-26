#include "MyTexture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include "OpenGLESHelper.h"


MyTexture::MyTexture(const char *fileName)
	: mFileName(fileName)
	, mTexture(0)
{

}

MyTexture::~MyTexture() {

}

void MyTexture::bind(GLuint program) {
	if (0 == mTexture) {
#if 0
		QImage img(QString::fromUtf8(mFileName.c_str()));
		//QImage tmp = QGLWidget::convertToGLFormat(img);
		QImage tmp = (img.format() == QImage::Format_RGB32 || img.format() == QImage::Format_ARGB32_Premultiplied)
			? img
			: img.convertToFormat(QImage::Format_ARGB32_Premultiplied);

		int width = tmp.width(), height = tmp.height();

		glGenTextures(1, &mTexture); CHECKERR();
		glBindTexture(GL_TEXTURE_2D, mTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, tmp.bits());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_2D);
#endif
	}
	glBindTexture(GL_TEXTURE_2D, mTexture);
}