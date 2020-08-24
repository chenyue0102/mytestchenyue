//
// Created by chenyue on 2020/8/24.
//

#ifndef TESTFFMPEG_OPENGLPLAY_H
#define TESTFFMPEG_OPENGLPLAY_H

#include "InterfaceDefine.h"

class OpenGLPlay : public IVideoPlay{
public:
    OpenGLPlay();
    ~OpenGLPlay();

public:
    virtual bool setVideoInfo(uint32_t format, uint32_t width, uint32_t height)override;
    virtual bool open()override ;
	virtual bool putData(uint8_t *data[], int32_t linesize[])override;
	virtual void draw()override ;
    virtual bool close()override ;

private:
    uint32_t mFormat;
    uint32_t mWidth;
    uint32_t mHeight;
	IVideoRender *mVideoRender;
};


#endif //TESTFFMPEG_OPENGLPLAY_H
