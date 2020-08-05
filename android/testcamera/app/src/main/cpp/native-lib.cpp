#include <jni.h>
#include <string>
#include <stddef.h>
#include <atomic>
#include <android/log.h>
#include "OpenSLESHelper.h"
#include "TaskPool.h"
#include "MacroDefine.h"
#include "Single.h"
#include "Log.h"
#include "RingQueue.h"
#include "byteswap.h"
#include "AudioRecordLogic.h"
#include "SystemTime.h"

OpenSLESHelper g_OpenSLESHelper;
TaskPool g_TaskPool;
std::string g_saveFile;
JavaVM *g_JavaVM = 0;
const int g_bufSize = 2048;
uint8_t g_buffer[g_bufSize] = {0};
AudioRecordLogic g_AudioRecordLogic;

//小端对齐
struct wav_fmt_header_t{
    char chunkID[4]; //"fmt " = 0x20746D66
    uint32_t chunkSize; //16 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
};
//Wav Header
struct wav_header_t
{
    char chunkID[4]; //"RIFF" = 0x46464952
    uint32_t chunkSize; //文件长度-8
    char format[4]; //"WAVE" = 0x45564157
    wav_fmt_header_t fmt;
};

//Chunks
struct chunk_t
{
    char chunkID[4];        //"data" = 0x61746164
    uint32_t chunkSize;     //Chunk data bytes
};

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved){
    g_JavaVM = vm;
    __android_log_write(ANDROID_LOG_DEBUG, "JNI", "JNI_OnLoad");
    g_TaskPool.Open(5);
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_testcamera_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void SLAPIENTRY RecordCallback(
        SLRecordItf caller,
        void *pContext,
        SLuint32 event){
    SC(Log).e("RecordCallback");
}

void SLAPIENTRY AndroidSimpleBufferQueueCallback(
        SLAndroidSimpleBufferQueueItf caller,
        void *pContext){
    //SC(Log).e("AndroidSimpleBufferQueueCallback");
    long long begin = SC(SystemTime).getCurrentTimeUs();
    g_AudioRecordLogic.appendData(g_buffer, g_bufSize);
    long long step2 = SC(SystemTime).getCurrentTimeUs();
    g_OpenSLESHelper.enqueueRecord(g_buffer, g_bufSize);
    long long step3 = SC(SystemTime).getCurrentTimeUs();
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    SC(Log).e("AndroidSimpleBufferQueueCallback first:%lld, second%lld total:%lld", step2 - begin, step3 - step2, step3 - begin);
}

void startRecord(){
    g_AudioRecordLogic.setOutputFormat(AudioRecordLogic::MP3);
    g_AudioRecordLogic.setInputStreamInfo(2, 44100, 16);
    g_AudioRecordLogic.setMp3BRate(256);
    g_AudioRecordLogic.startRecord(g_saveFile.c_str());
    g_OpenSLESHelper.createEngine();
    g_OpenSLESHelper.createRecord(&RecordCallback, nullptr, &AndroidSimpleBufferQueueCallback, nullptr);
    g_OpenSLESHelper.enqueueRecord(g_buffer, g_bufSize);
    g_OpenSLESHelper.setRecordState(SL_RECORDSTATE_RECORDING);
}

void stopRecord(){
    g_OpenSLESHelper.setRecordState(SL_RECORDSTATE_STOPPED);
    g_OpenSLESHelper.destroyRecord();
    g_OpenSLESHelper.destroy();
    g_AudioRecordLogic.stopRecord();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_test_testcamera_MainActivity_recordC(JNIEnv *env, jobject thiz, jstring file_path) {
    jboolean iscopy = 0;
    const char *str = env->GetStringUTFChars(file_path, &iscopy);
    if (nullptr != str){
        g_saveFile = str;
        g_TaskPool.AddTask(&startRecord);
        env->ReleaseStringUTFChars(file_path, str);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_test_testcamera_MainActivity_stopRecordC(JNIEnv *env, jobject thiz) {
    stopRecord();
}