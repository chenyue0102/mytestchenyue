#ifndef Spine_OpenGLES_H_
#define Spine_OpenGLES_H_

#ifdef __IPHONEOS__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#elif WIN32
#include <GL/glew.h>
#else
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#include "SpineBase.h"

namespace spine {
	
class TextureOpenGLES : public TextureBase {
public:
	TextureOpenGLES(const char *path);
	virtual ~TextureOpenGLES();

public:
	virtual int width()const;
	virtual int height()const;
	GLuint getTexture()const { return mTexture; }
private:
	void doInit(const char *path);

private:
	GLuint mTexture;
	int mWidth;
	int mHeight;
};

class RenderOpenGLES : public RenderBase {
public:
	RenderOpenGLES();
	virtual ~RenderOpenGLES();
public:
	virtual void draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray)override;
private:
	void doInit();
	void doDestroy();

private:
	GLuint mProgram;
	GLuint mBuffer;
	GLuint mVertex;
};

class SkeletonDrawableOpenGLES : public SkeletonDrawableBase {
public:
	SkeletonDrawableOpenGLES();
	virtual ~SkeletonDrawableOpenGLES();

public:
	virtual TextureBase* createTexture(const char *path)override;

protected:
	virtual void onListenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event)override;
};
}

#endif