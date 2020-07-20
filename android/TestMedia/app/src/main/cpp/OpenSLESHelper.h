//
// Created by EDZ on 2020/7/20.
//

#ifndef TESTMEDIA_OPENSLESHELPER_H
#define TESTMEDIA_OPENSLESHELPER_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>//SLAndroidSimpleBufferQueueItf

struct OpenSLESHelperData;
class OpenSLESHelper {
public:
    OpenSLESHelper();
    ~OpenSLESHelper();

public:
    bool createEngine();
    bool destroy();
    bool createOutputMix();
    bool createPlayer(SLDataSource &slDataSource, SLDataSink &slDataSink, SLuint32 numInterfaces, const SLInterfaceID ids[], const SLboolean req[]);
    bool destroyPlayer();
    bool registerBufferQueueCallback(slAndroidSimpleBufferQueueCallback callback, void *pContext);

public:
    //SL_PLAYSTATE_PLAYING, SL_PLAYSTATE_PAUSED, SL_PLAYSTATE_STOPPED
    bool setPlayState(SLuint32 playState);

public:
    SLObjectItf getEngineObject()const;
    SLObjectItf getOutputMixObject()const;
    SLObjectItf getPlayerObject()const;
    SLAndroidSimpleBufferQueueItf getBufferQueue()const;
private:
    OpenSLESHelperData *mData;
};


#endif //TESTMEDIA_OPENSLESHELPER_H
