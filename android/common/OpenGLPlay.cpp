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
    , mXRotate()
    , mYRotate()
    , mZRotate()
    , mVideoRender(nullptr){

}

OpenGLPlay::~OpenGLPlay() {
    delete mVideoRender;
    mVideoRender = nullptr;
}

bool OpenGLPlay::setVideoInfo(uint32_t format, uint32_t width, uint32_t height) {
    std::lock_guard<std::mutex> lk(mMutex);

    mFormat = format;
    mWidth = width;
    mHeight = height;
    return true;
}

bool OpenGLPlay::setRotate(float x, float y, float z) {
    std::lock_guard<std::mutex> lk(mMutex);

    mXRotate = x;
    mYRotate = y;
    mZRotate = z;
    return true;
}

bool OpenGLPlay::open() {
    std::lock_guard<std::mutex> lk(mMutex);

	switch (mFormat) {
	case EVideoFormatYUV420P:
        mVideoRender = new RenderYUV420P(mWidth, mHeight);
		mVideoRender->setRotate(mXRotate, mYRotate, mZRotate);
		break;
	}
    return true;
}

bool OpenGLPlay::putData(uint8_t * data[], int32_t linesize[]){
    std::lock_guard<std::mutex> lk(mMutex);

    if (nullptr != mVideoRender){
        mVideoRender->putData(data, linesize);
    }
	return true;
}

void OpenGLPlay::draw() {
    std::lock_guard<std::mutex> lk(mMutex);

    if (nullptr != mVideoRender){
        mVideoRender->draw();
    }
}

bool OpenGLPlay::close() {
    std::lock_guard<std::mutex> lk(mMutex);

    if (nullptr != mVideoRender){
        delete mVideoRender;
        mVideoRender = nullptr;
    }
    return true;
}
