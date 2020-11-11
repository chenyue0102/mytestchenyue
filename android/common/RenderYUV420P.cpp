//
// Created by EDZ on 2020/8/24.
//

#include "RenderYUV420P.h"
#include <assert.h>
#include "OpenGLHelper.h"
#include "vmath.h"

#ifdef _WIN32
#define GLSL_VERSION_TEXT "#version 430 core\n"
#else
#define GLSL_VERSION_TEXT "#version 310 es\n" "precision mediump float;\n"
#endif
static const char *g_VString = GLSL_VERSION_TEXT R"(
layout(location=0) in vec2 vPosition;
layout(location=1) in vec2 tPosition;
layout(location=3) uniform mat4 matrix;
out vec2 texPosition;
void main(){
    gl_Position = matrix * vec4(vPosition, 0.0f, 1.0f);
    texPosition = tPosition;
}
)";

static const char *g_FString = GLSL_VERSION_TEXT R"(
layout(location=0) uniform sampler2D yTex;
layout(location=1) uniform sampler2D uTex;
layout(location=2) uniform sampler2D vTex;
in vec2 texPosition;
out vec4 fColor;
void main(){
    vec3 yuv, rgb;
    yuv.x = texture(yTex, texPosition).r;
    yuv.y = texture(uTex, texPosition).r - 0.5;
    yuv.z = texture(vTex, texPosition).r - 0.5;
    rgb = mat3(1.0, 1.0, 1.0,
					0.0, -0.39465, 2.03211,
					1.13983, -0.58060, 0.0) * yuv;
    //gl_FragColor = vec4(rgb, 1.0f);
    fColor = vec4(rgb, 1.0f);
}
)";

RenderYUV420P::RenderYUV420P(uint32_t width, uint32_t height)
        : mInit(false)
        , mWidth(width)
        , mHeight(height)
        , mXRotate()
        , mYRotate()
        , mZRotate()
        , mTextures()
        , mProgram()
        , mVertex()
        , mBuffer()
        , mDataBuffer()
        , mBufferChanged(false)
        , mLineSize(){

}

RenderYUV420P::~RenderYUV420P() {
    glDeleteTextures(3, mTextures);
    glDeleteProgram(mProgram);
    glDeleteVertexArrays(1, &mVertex);
    glDeleteBuffers(1, &mBuffer);
}

bool RenderYUV420P::setRotate(float x, float y, float z) {
    mXRotate = x;
    mYRotate = y;
    mZRotate = z;
    return true;
}

void RenderYUV420P::putData(uint8_t *data[], int32_t linesize[]) {
    memcpy(mLineSize, linesize, sizeof(mLineSize));
	uint32_t heights[] = { mHeight, mHeight / 2, mHeight / 2 };
    for (int i = 0; i < 3; i++){
        int32_t size = mLineSize[i] * heights[i];
        mDataBuffer[i].resize(size);
        memcpy(mDataBuffer[i].data(), data[i], size);
    }
    mBufferChanged = true;
}

void RenderYUV420P::draw() {
    if (!mInit){
        mInit = true;
        init();
    }

    if (mBufferChanged){
        mBufferChanged = false;
        updateTexture();
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(mProgram);CHECKERR();

    uint32_t widths[] = {mWidth, mWidth / 2, mWidth / 2};
    uint32_t heights[] = {mHeight, mHeight / 2, mHeight / 2};
    for (int i = 0; i < 3; i++){
        glActiveTexture(GL_TEXTURE0 + i);CHECKERR();
        glBindTexture(GL_TEXTURE_2D, mTextures[i]);CHECKERR();
        GLint location = i;
        glUniform1i(location, i);CHECKERR();
    }

	vmath::mat4 matrix = vmath::rotate(mXRotate, mYRotate, mZRotate);
    glUniformMatrix4fv(3, 1, GL_FALSE, matrix);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);CHECKERR();
    glFlush();CHECKERR();
}

void RenderYUV420P::init() {
    glGenTextures(3, mTextures);CHECKERR();
    GLenum err = OpenGLHelper::setTexture2D(mTextures[0], GL_RED, mWidth, mHeight, GL_RED, GL_UNSIGNED_BYTE, GL_LINEAR);
    assert(GL_NO_ERROR == err);
    err = OpenGLHelper::setTexture2D(mTextures[1], GL_RED, mWidth / 2, mHeight / 2, GL_RED, GL_UNSIGNED_BYTE, GL_LINEAR);
    assert(GL_NO_ERROR == err);
    err = OpenGLHelper::setTexture2D(mTextures[2], GL_RED, mWidth / 2, mHeight / 2, GL_RED, GL_UNSIGNED_BYTE, GL_LINEAR);
    assert(GL_NO_ERROR == err);

    mProgram = glCreateProgram();
    err = OpenGLHelper::attachShader(mProgram, GL_VERTEX_SHADER, g_VString, 0);
    assert(GL_NO_ERROR == err);
    err = OpenGLHelper::attachShader(mProgram, GL_FRAGMENT_SHADER, g_FString, 0);
    assert(GL_NO_ERROR == err);
    glLinkProgram(mProgram);CHECKERR();

    const GLfloat vertexs[][2] = {
            {-1.0f, -1.0f},
            {1.0f, -1.0f},
            {-1.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f},
    };
    glGenBuffers(1, &mBuffer);CHECKERR();
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);CHECKERR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);CHECKERR();
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &mVertex);CHECKERR();
    glBindVertexArray(mVertex);CHECKERR();
    GLuint buffer = 0;
    glGenBuffers(1, &buffer);CHECKERR();
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);CHECKERR();
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));CHECKERR();
    glEnableVertexAttribArray(0);CHECKERR();
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(GLfloat) * 8));CHECKERR();
    glEnableVertexAttribArray(1);CHECKERR();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderYUV420P::updateTexture() {
    glBindTexture(GL_TEXTURE_2D, mTextures[0]);CHECKERR();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mWidth, mHeight, 0, GL_RED, GL_UNSIGNED_BYTE, mDataBuffer[0].data());CHECKERR();
    glBindTexture(GL_TEXTURE_2D, mTextures[1]);CHECKERR();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mWidth / 2, mHeight / 2, 0, GL_RED, GL_UNSIGNED_BYTE, mDataBuffer[1].data());CHECKERR();
    glBindTexture(GL_TEXTURE_2D, mTextures[2]);CHECKERR();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, mWidth / 2, mHeight / 2, 0, GL_RED, GL_UNSIGNED_BYTE, mDataBuffer[2].data());CHECKERR();
    glBindTexture(GL_TEXTURE_2D, 0);CHECKERR();
}
