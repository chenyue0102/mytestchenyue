#include "SpineOpenGLES.h"
#include <assert.h>
#include "OpenGLESHelper.h"
#ifdef WIN32
#include "../SDL2_image/SDL_image.h"
#endif

namespace spine {
#ifdef WIN32
#define GLSLVERSION "#version 430 core"
#else
#define GLSLVERSION "#version 300 es"
#endif
const char *g_vString = GLSLVERSION
R"(
in vec3 vertexPosition;
in vec2 texturePosition;
uniform float viewWidth;
uniform float viewHeight;
out vec2 esTexturePosition;
void main(){
	float x = (vertexPosition.x / viewWidth) * 2 - 1.0f;
	float y = (vertexPosition.y / viewHeight) * 2 - 1.0f;
	gl_Position = vec4(x, y, 0.f, 1.0f);
	esTexturePosition = texturePosition;
})";

const char *g_fString = GLSLVERSION
R"(
precision mediump float;
uniform sampler2D tex;
in vec2 esTexturePosition;
out vec4 fColor;
void main() {
	fColor = texture(tex, esTexturePosition);
})";


TextureOpenGLES::TextureOpenGLES(const char *path)
	: TextureBase()
	, mTexture(0)
	, mWidth(0)
	, mHeight(0)
{
	doInit(path);
}

TextureOpenGLES::~TextureOpenGLES() {
	if (0 != mTexture) {
		glDeleteTextures(1, &mTexture);
		mTexture = 0;
	}
}

int TextureOpenGLES::width()const {
	return mWidth;
}

int TextureOpenGLES::height()const {
	return mHeight;
}

void TextureOpenGLES::doInit(const char *path) {
	bool success = false;
	GLenum err = GL_NO_ERROR;
	GLint internalformat = 0;
	GLenum format = 0;
	GLenum type = 0;
	const void *pixels = nullptr;	//4byte¶ÔÆë
#ifdef WIN32
	SDL_Surface *surface = IMG_Load(path);
	if (nullptr == surface) {
		assert(false);
		return;
	}
	internalformat = GL_RGBA;
	mWidth = surface->w;
	mHeight = surface->h;
	pixels = surface->pixels;
	format = GL_RGBA;
	type = GL_UNSIGNED_BYTE;
#else
#endif
	do
	{
		glGenTextures(1, &mTexture); CHECK_BREAK;
		glBindTexture(GL_TEXTURE_2D, mTexture); CHECK_BREAK;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, internalformat, mWidth, mHeight, 0, format, type, pixels); CHECK_BREAK;
		glBindTexture(GL_TEXTURE_2D, 0); CHECK_BREAK;

		success = true;
	} while (false);
	
	if (!success && 0 != mTexture) {
		glDeleteTextures(1, &mTexture);
		mTexture = 0;
	}

#ifdef WIN32
	if (nullptr != surface) {
		SDL_FreeSurface(surface);
		surface = nullptr;
	}

#else
#endif
}


RenderOpenGLES::RenderOpenGLES()
	: RenderBase()
	, mProgram(0)
	, mBuffer(0)
	, mVertex(0)
{
	doInit();
}

RenderOpenGLES::~RenderOpenGLES() {
	doDestroy();
}

void RenderOpenGLES::draw(TextureBase *texture, BlendMode blendMode, PrimitiveType type, const std::vector<Vertex> *vertexArray) {
	if (nullptr == texture || nullptr == vertexArray || vertexArray->empty()) {
		return;
	}
	/*GLfloat f[][4] = {
		{-1.0f, -1.f, 0.f, 0.f},
	{1.f, -1.f, 1.f, 0.f},
	{-1.f, 1.f, 0.f, 1.f},
	{1.f, 1.f, 1.f, 1.f}
	};
	std::vector<Vertex> tmp;
	vertexArray = &tmp;
	for (auto &ff : f) {
		Vertex v;
		v.position.x = ff[0];
		v.position.y = ff[1];
		v.texCoords.x = ff[2];
		v.texCoords.y = ff[3];
		tmp.push_back(v);
	}*/
	
	TextureOpenGLES *textureOpenGLES = (TextureOpenGLES*)texture;
	GLenum err = GL_NO_ERROR;
	do
	{
		glUseProgram(mProgram); CHECK_BREAK;
		glBindVertexArray(mVertex); CHECK_BREAK;
		glBindBuffer(GL_ARRAY_BUFFER, mBuffer); CHECK_BREAK;
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexArray->size(), vertexArray->data(), GL_STATIC_DRAW);

		int viewWidthLocation = glGetUniformLocation(mProgram, "viewWidth"); CHECK_BREAK;
		glUniform1f(viewWidthLocation, (float)viewWidth()); CHECK_BREAK;

		int viewHeightLocation = glGetUniformLocation(mProgram, "viewHeight"); CHECK_BREAK;
		glUniform1f(viewHeightLocation, (float)viewHeight());

		int vertexLocation = glGetAttribLocation(mProgram, "vertexPosition"); CHECK_BREAK;
		glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, false, sizeof(Vertex), BUFFER_OFFSET(0)); CHECK_BREAK;
		glEnableVertexAttribArray(vertexLocation); CHECK_BREAK;

		int texLocation = glGetAttribLocation(mProgram, "texturePosition"); CHECK_BREAK;
		glVertexAttribPointer(texLocation, 2, GL_FLOAT, false, sizeof(Vertex), BUFFER_OFFSET(sizeof(Vector2f) + sizeof(Color))); CHECK_BREAK;
		glEnableVertexAttribArray(texLocation); CHECK_BREAK;

		glActiveTexture(GL_TEXTURE0); CHECK_BREAK;
		glBindTexture(GL_TEXTURE_2D, textureOpenGLES->getTexture()); CHECK_BREAK;
		GLint texUniformLocation = glGetUniformLocation(mProgram, "tex"); CHECK_BREAK;
		glUniform1i(texUniformLocation, 0); CHECK_BREAK;

		glDrawArrays(GL_TRIANGLES, 0, vertexArray->size()); CHECK_BREAK;

	} while (false);
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderOpenGLES::doInit() {
	GLenum err = GL_NO_ERROR;
	bool success = false;
	do
	{
		if (0 == (mProgram = glCreateProgram())) {
			assert(false);
			break;
		}
		if (GL_NO_ERROR != (err = OpenGLESHelper::attachShader(mProgram, GL_VERTEX_SHADER, g_vString, 0))) {
			assert(false);
			break;
		}
		if (GL_NO_ERROR != (err = OpenGLESHelper::attachShader(mProgram, GL_FRAGMENT_SHADER, g_fString, 0))) {
			assert(false);
			break;
		}
		glLinkProgram(mProgram); CHECK_BREAK;

		glGenVertexArrays(1, &mVertex); CHECK_BREAK;
		glGenBuffers(1, &mBuffer); CHECK_BREAK;
		success = true;
	} while (false);
	if (!success) {
		doDestroy();
	}
}

void RenderOpenGLES::doDestroy() {
	if (0 != mProgram) {
		glDeleteProgram(mProgram);
		mProgram = 0;
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