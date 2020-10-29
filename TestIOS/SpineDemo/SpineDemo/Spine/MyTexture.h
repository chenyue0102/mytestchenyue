#ifndef My_Texture_h_
#define My_Texture_h_
#include <string>
#ifdef WIN32
#include <GL/glew.h>
#else
#include <OpenGLES/ES3/gl.h>
#endif

class MyTexture {
public:
	MyTexture(const char *fileName);
	virtual ~MyTexture();

public:
	void bind();
private:
	std::string mFileName;
	GLuint mTexture;
};

#endif
