#include "SpineOpenGLES.h"
#include <assert.h>
#include "OpenGLESHelper.h"

namespace spine {
const char *g_vString = R"(
)";


TextureOpenGLES::TextureOpenGLES(const char *path)
	: TextureBase()
	, mTexture(0)
	, mBuffer(0)
	, mVertex(0)
	, mWidth(0)
	, mHeight(0)
{
	glGenTextures(1, &mTexture);
}

TextureOpenGLES::~TextureOpenGLES() {
	if (0 != mTexture) {
		glDeleteTextures(1, &mTexture);
		mTexture = 0;
	}
	if (0 != mBuffer) {
		glDeleteBuffers(1, &mBuffer);
		mBuffer = 0;
	}
	if (0 != mVertex) {
		glDeleteVertexArrays(1, &mVertex);
		mVertex = 0;
	}
}

int TextureOpenGLES::width()const {
	return mWidth;
}

int TextureOpenGLES::height()const {
	return mHeight;
}


RenderOpenGLES::RenderOpenGLES()
	: RenderBase()
{

}

RenderOpenGLES::~RenderOpenGLES() {

}

void RenderOpenGLES::draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray) {

}


SkeletonDrawableOpenGLES::SkeletonDrawableOpenGLES()
	: SkeletonDrawableBase()
{

}

SkeletonDrawableOpenGLES::~SkeletonDrawableOpenGLES() {

}

TextureBase* SkeletonDrawableOpenGLES::createTexture(const char *path) {
	TextureOpenGLES *texture = new TextureOpenGLES(path);
	if (0 == texture->width() || 0 == texture->height()) {
		assert(false);
		delete texture;
		return nullptr;
	}
	else {
		return texture;
	}
}

void SkeletonDrawableOpenGLES::onListenAnimations(spAnimationState* state, spEventType type, spTrackEntry* entry, spEvent* event) {
	switch (type)
	{
	case SP_ANIMATION_START:
	{

	}
	break;
	case SP_ANIMATION_COMPLETE:
	{

	}
	break;
	default:

		break;
	}
}
}