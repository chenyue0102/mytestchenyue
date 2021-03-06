//
// Created by EDZ on 2020/7/20.
//

#include "OpenSLESHelper.h"
#include <assert.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>//SLAndroidSimpleBufferQueueItf
#include "Log.h"
#include "Single.h"
#include "MacroDefine.h"

#define REFALL \
    REFM(slEngineObject); \
    REFM(slEngine); \
    REFM(slOutputMixObject); \
    REFM(slEnvironmentalReverb); \
    REFM(slPlayerObject); \
    REFM(slPlay); \
    REFM(slPlayBufferQueue); \
    REFM(slVolume)

struct OpenSLESHelperData{
    SLObjectItf slEngineObject;
    SLEngineItf slEngine;

    SLObjectItf slOutputMixObject;
    SLEnvironmentalReverbItf slEnvironmentalReverb;

    SLObjectItf slPlayerObject;
    SLPlayItf slPlay;
    SLAndroidSimpleBufferQueueItf slPlayBufferQueue;
    SLVolumeItf slVolume;
};
static bool isEqual(const SLInterfaceID &left, const SLInterfaceID &right){
    return 0 == memcmp(left, right, sizeof(SLInterfaceID_));
}
OpenSLESHelper::OpenSLESHelper() :mData(new OpenSLESHelperData()){

}

OpenSLESHelper::~OpenSLESHelper() {
    destroy();
    delete mData;
    mData = nullptr;
}

bool OpenSLESHelper::createEngine() {
    REFALL;
    SLresult result;
    bool ret = false;

    do{
        destroy();
        if ((result = slCreateEngine(&slEngineObject, 0, nullptr, 0, nullptr, nullptr)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createEngine slCreateEngine failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slEngineObject)->Realize(slEngineObject, SL_BOOLEAN_FALSE)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createEngine Realize failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slEngineObject)->GetInterface(slEngineObject, SL_IID_ENGINE, &slEngine)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createEngine GetInterface failed result:%x", result);
            assert(false);
            break;
        }
        ret = true;
    }while(false);

    if (!ret){
        destroy();
    }
    return ret;
}

bool OpenSLESHelper::destroy() {
    REFALL;
    destroyOutputMix();
    destroyPlayer();

    if (nullptr != slEngineObject){
        (*slEngineObject)->Destroy(slEngineObject);
        slEngineObject = nullptr;
        slEngine = nullptr;
    }
    return true;
}

bool OpenSLESHelper::createOutputMix() {
    REFALL;
    bool ret = false;
    SLresult result;

    do{
        destroyOutputMix();
        if (nullptr == slEngine){
            SC(Log).e("OpenSLESHelper::createOutputMix failed nullptr == slEngine");
            assert(false);
            break;
        }
        const SLInterfaceID ids[] = {SL_IID_ENVIRONMENTALREVERB};
        const SLboolean req[] = {SL_BOOLEAN_FALSE};
        if ((result = (*slEngine)->CreateOutputMix(slEngine, &slOutputMixObject, 1, ids, req)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createOutputMix CreateOutputMix failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slOutputMixObject)->Realize(slOutputMixObject, SL_BOOLEAN_FALSE)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createOutputMix Realize failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slOutputMixObject)->GetInterface(slOutputMixObject, SL_IID_ENVIRONMENTALREVERB, &slEnvironmentalReverb)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createOutputMix GetInterface failed result:%x", result);
            assert(false);
            break;
        }
        ret = true;
    }while (false);

    if (!ret){
        destroyOutputMix();
    }
    return ret;
}

bool OpenSLESHelper::destroyOutputMix() {
    REFALL;
    if (nullptr != slOutputMixObject){
        (*slOutputMixObject)->Destroy(slOutputMixObject);
        slOutputMixObject = nullptr;
    }
    slEnvironmentalReverb = nullptr;
    return true;
}

bool OpenSLESHelper::setEnvironmentalReverbProperties(const SLEnvironmentalReverbSettings &reverbSettings) {
    REFALL;
    bool ret = false;
    SLresult result;

    do{
        if (nullptr == slEnvironmentalReverb){
            SC(Log).e("OpenSLESHelper::setEnvironmentalReverbProperties failed nullptr == slEnvironmentalReverb");
            assert(false);
            break;
        }
        if ((result = (*slEnvironmentalReverb)->SetEnvironmentalReverbProperties(slEnvironmentalReverb, &reverbSettings)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::setEnvironmentalReverbProperties SetEnvironmentalReverbProperties failed result:%x", result);
            assert(false);
            break;
        }
        ret = true;
    }while(false);

    return ret;
}

bool OpenSLESHelper::createPlayer(SLDataSource &slDataSource, SLDataSink &slDataSink, SLuint32 numInterfaces, const SLInterfaceID ids[], const SLboolean req[]) {
    REFALL;
    bool ret = false;
    SLresult result;

    do{
        destroyPlayer();
        if (nullptr == slEngine){
            SC(Log).e("OpenSLESHelper::createPlayer failed nullptr == slEngine");
            assert(false);
            break;
        }
        if ((result = (*slEngine)->CreateAudioPlayer(slEngine, &slPlayerObject, &slDataSource, &slDataSink, numInterfaces, ids, req)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createPlayer CreateAudioPlayer failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slPlayerObject)->Realize(slPlayerObject, SL_BOOLEAN_FALSE)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createPlayer Realize failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slPlayerObject)->GetInterface(slPlayerObject, SL_IID_PLAY, &slPlay)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createPlayer GetInterface SL_IID_PLAY failed result:%x", result);
            assert(false);
            break;
        }
        if ((result = (*slPlayerObject)->GetInterface(slPlayerObject, SL_IID_BUFFERQUEUE, &slPlayBufferQueue)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createPlayer GetInterface SL_IID_BUFFERQUEUE failed result:%x", result);
        }
        if ((result = (*slPlayerObject)->GetInterface(slPlayerObject, SL_IID_VOLUME, &slVolume)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::createPlayer GetInterface SL_IID_VOLUME failed result:%x", result);
        }
        ret = true;
    }while(false);

    if (!ret){
        destroyPlayer();
    }
    return ret;
}

bool OpenSLESHelper::destroyPlayer() {
    REFALL;

    if (nullptr != slPlayerObject){
        (*slPlayerObject)->Destroy(slPlayerObject);
        slPlayerObject = nullptr;
    }
    slPlay = nullptr;
    slPlayBufferQueue = nullptr;
    slVolume = nullptr;
    return true;
}

bool OpenSLESHelper::registerBufferQueueCallback(slAndroidSimpleBufferQueueCallback callback, void *pContext) {
    REFALL;
    bool ret = false;
    SLresult result;

    do{
        if (nullptr == callback){
            SC(Log).e("OpenSLESHelper::registerBufferQueueCallback failed nullptr == callback");
            assert(false);
            break;
        }
        if (nullptr == slPlayBufferQueue){
            SC(Log).e("OpenSLESHelper::registerBufferQueueCallback failed nullptr == slPlayBufferQueue");
            assert(false);
            break;
        }
        if ((result = (*slPlayBufferQueue)->RegisterCallback(slPlayBufferQueue, callback, pContext)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::registerBufferQueueCallback RegisterCallback failed result:%x", result);
            assert(false);
            break;
        }
        ret = true;
    }while(false);
    return ret;
}

bool OpenSLESHelper::setPlayState(SLuint32 playState) {
    REFALL;
    bool ret = false;
    SLresult result;

    do{
        if (nullptr == slPlay){
            SC(Log).e("OpenSLESHelper::setPlayState failed nullptr == slPlay");
            assert(false);
            break;
        }
        if ((result = (*slPlay)->SetPlayState(slPlay, playState)) != SL_RESULT_SUCCESS){
            SC(Log).e("OpenSLESHelper::setPlayState SetPlayState failed result:%x", result);
            assert(false);
            break;
        }
    }while(false);
    return ret;
}

SLObjectItf OpenSLESHelper::getEngineObject() const {
    return mData->slEngineObject;
}

SLObjectItf OpenSLESHelper::getOutputMixObject() const {
    return mData->slOutputMixObject;
}

SLObjectItf OpenSLESHelper::getPlayerObject() const {
    return mData->slPlayerObject;
}

SLAndroidSimpleBufferQueueItf OpenSLESHelper::getBufferQueue() const {
    return mData->slPlayBufferQueue;
}

SLPlayItf OpenSLESHelper::getPlay() const {
    return mData->slPlay;
}

