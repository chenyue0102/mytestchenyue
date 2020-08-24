//
// Created by EDZ on 2020/8/24.
//

#include "OpenGLPlay.h"
#include "EnumDefine.h"
#include "RenderYUV420P.h"

OpenGLPlay::OpenGLPlay()
    : mFormat()
    , mWidth()
    , mHeight()
    , mVideoRender(nullptr){

}

OpenGLPlay::~OpenGLPlay() {
    delete mVideoRender;
    mVideoRender = nullptr;
}

bool OpenGLPlay::setVideoInfo(uint32_t format, uint32_t width, uint32_t height) {
    mFormat = format;
    mWidth = width;
    mHeight = height;
    return true;
}

bool OpenGLPlay::open() {
	switch (mFormat) {
	case EVideoFormatYUV420P:
        mVideoRender = new RenderYUV420P(mWidth, mHeight);
		break;
	}
    return true;
}

bool OpenGLPlay::putData(uint8_t * data[], int32_t linesize[])
{
    if (nullptr != mVideoRender){
        mVideoRender->putData(data, linesize);
    }
	return true;
}

void OpenGLPlay::draw() {
    if (nullptr != mVideoRender){
        mVideoRender->draw();
    }
}

bool OpenGLPlay::close() {
    if (nullptr != mVideoRender){
        delete mVideoRender;
        mVideoRender = nullptr;
    }
    return true;
}
