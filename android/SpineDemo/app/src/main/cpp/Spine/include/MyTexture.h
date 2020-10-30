#ifndef My_Texture_h_
#define My_Texture_h_
#include <string>

#ifdef WIN32
#include <GL/glew.h>
#elif defined __ANDROID__
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#elif defined __APPLE__
#include <OpenGLES/ES3/glext.h>
#else
#error "platform unknown"
#endif

class MyTexture {
public:
	MyTexture(const char *fileName);
	virtual ~MyTexture();

public:
	void bind();
	void unbind();

private:
	std::string mFileName;
	GLuint mTexture;
};

#endif
