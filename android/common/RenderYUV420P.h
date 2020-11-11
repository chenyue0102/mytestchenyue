//
// Created by chenyue on 2020/8/24.
//

#ifndef TESTFFMPEG_RENDERYUV420P_H
#define TESTFFMPEG_RENDERYUV420P_H

#include <stdint.h>
#include <mutex>
#include <vector>
#ifdef _WIN32
#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#else
#include <GLES3/gl3.h>
extern "C"{
#include <android/log.h>
};
#endif

#include "InterfaceDefine.h"

class RenderYUV420P : public IVideoRender{
public:
    RenderYUV420P(uint32_t width, uint32_t height);
    ~RenderYUV420P();

public:
    virtual bool setRotate(float x, float y, float z);
    //
    virtual void putData(uint8_t *data[], int32_t linesize[]);
    //主线程调用
    virtual void draw();

private:
    //主线程调用
    void init();
    //主线程调用
    void updateTexture();
private:
    bool mInit;
    uint32_t mWidth;
    uint32_t mHeight;
    float mXRotate;
    float mYRotate;
    float mZRotate;
    GLuint mTextures[3];
    GLuint mProgram;
    GLuint mVertex;
    GLuint mBuffer;

    std::vector<uint8_t> mDataBuffer[3];
    bool mBufferChanged;
    int32_t mLineSize[3];
};


#endif //TESTFFMPEG_RENDERYUV420P_H
