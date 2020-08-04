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

public:
    bool createOutputMix();
    bool destroyOutputMix();
    //
    bool setEnvironmentalReverbProperties(const SLEnvironmentalReverbSettings &reverbSettings);

public:
    bool createPlayer(SLDataSource &slDataSource, SLDataSink &slDataSink, SLuint32 numInterfaces, const SLInterfaceID ids[], const SLboolean req[]);
    bool destroyPlayer();
    bool registerBufferQueueCallback(slAndroidSimpleBufferQueueCallback callback, void *pContext);
    //SL_PLAYSTATE_PLAYING, SL_PLAYSTATE_PAUSED, SL_PLAYSTATE_STOPPED
    bool setPlayState(SLuint32 playState);

public:
    bool createRecord(slRecordCallback recordCallback, void *pRecordContext,
            slAndroidSimpleBufferQueueCallback recorderBufferQueueCallback, void *pBufferQueueContext);
    bool destroyRecord();
    bool enqueueRecord(void *buffer, size_t size);
    //SL_RECORDSTATE_RECORDING SL_RECORDSTATE_STOPPED SL_RECORDSTATE_PAUSED
    bool setRecordState(int state);

public:
    SLObjectItf getEngineObject()const;
    SLObjectItf getOutputMixObject()const;
    SLObjectItf getPlayerObject()const;
    SLAndroidSimpleBufferQueueItf getBufferQueue()const;
private:
    OpenSLESHelperData *mData;
};


#endif //TESTMEDIA_OPENSLESHELPER_H
