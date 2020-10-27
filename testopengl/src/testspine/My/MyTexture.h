#ifndef My_Texture_h_
#define My_Texture_h_
#include <string>
#include <GL/glew.h>

class MyTexture {
public:
	MyTexture(const char *fileName);
	virtual ~MyTexture();

public:
	void bind(GLuint program);
private:
	std::string mFileName;
	GLuint mTexture;
};

#endif