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

OpenSLESHelper g_OpenSLESHelper;
TaskPool g_TaskPool;
RingQueue g_RingQueue = RingQueue(1024 * 1024 * 2);
std::mutex g_mutex;
std::condition_variable g_cv;
std::string g_saveFile;
JavaVM *g_JavaVM = 0;
const int g_bufSize = 2048;
uint8_t g_buffer[g_bufSize] = {0};
std::atomic<bool> g_exit;

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
    SC(Log).e("AndroidSimpleBufferQueueCallback");
    {
        std::lock_guard<std::mutex> lk(g_mutex);
        g_RingQueue.put(g_buffer, g_bufSize);
        g_cv.notify_one();
    }

    g_OpenSLESHelper.enqueueRecord(g_buffer, g_bufSize);
}

void adjustPCMWavHeader(FILE *file, size_t dataCount, uint16_t numChannels, uint32_t sampleRate, uint16_t bitsPerSample){
    wav_header_t wavHeader = {0};
    memcpy(wavHeader.chunkID, "RIFF", 4);
    wavHeader.chunkSize = ByteSwap::htole32(sizeof(wav_header_t) - 8 + sizeof(chunk_t) + dataCount);
    memcpy(wavHeader.format, "WAVE", 4);
    memcpy(wavHeader.fmt.chunkID, "fmt ", 4);
    wavHeader.fmt.chunkSize = ByteSwap::htole32(sizeof(wav_fmt_header_t) - 8);
    wavHeader.fmt.audioFormat = ByteSwap::htole16(0x0001);
    wavHeader.fmt.numChannels = ByteSwap::htole16(numChannels);
    wavHeader.fmt.sampleRate = ByteSwap::htole32(sampleRate);
    uint32_t byteRate = sampleRate * numChannels * bitsPerSample / 8;
    wavHeader.fmt.byteRate = ByteSwap::htole32(byteRate);
    uint16_t blockAlign = bitsPerSample * numChannels / 8;
    wavHeader.fmt.blockAlign = ByteSwap::htole16(blockAlign);
    wavHeader.fmt.bitsPerSample = ByteSwap::htole16(bitsPerSample);
    fseek(file, 0, SEEK_SET);
    fwrite(&wavHeader, 1, sizeof(wavHeader), file);
    chunk_t chunk = {0};
    memcpy(chunk.chunkID, "data", 4);
    chunk.chunkSize = ByteSwap::htole32(dataCount);
    fwrite(&chunk, 1, sizeof(chunk), file);
}

void saveFile(){
    char szTmpBuffer[1024] = {0};
    FILE *file = fopen(g_saveFile.c_str(), "wb+");
    fseek(file, sizeof(wav_header_t) + sizeof(chunk_t), SEEK_SET);
    size_t saveCount = 0;
    size_t dataSize = 0;
    if (nullptr != file){
        while(!g_exit){
            std::unique_lock<std::mutex> lk(g_mutex);
            g_cv.wait(lk, [](){return g_exit || g_RingQueue.getDataSize() > 0;});
            lk.unlock();
            while(!g_exit && g_RingQueue.getDataSize() > 0){
                dataSize = g_RingQueue.get(szTmpBuffer, 1024);
                if (dataSize > 0){
                    if (fwrite(szTmpBuffer, 1, dataSize, file) != dataSize){
                        assert(false);
                        break;
                    }
                    saveCount += dataSize;
                }else{
                    break;
                }
            }
        }
        while(g_RingQueue.getDataSize() > 0 && (dataSize = g_RingQueue.get(szTmpBuffer, 1024)) > 0){
            if (fwrite(szTmpBuffer, 1, dataSize, file) != dataSize){
                assert(false);
                break;
            }
            saveCount += dataSize;
        }
        adjustPCMWavHeader(file, saveCount, 2, 44100, 16);
        fclose(file);
    }
}

void startRecord(){
    g_TaskPool.AddTask(&saveFile);
    g_OpenSLESHelper.createEngine();
    g_OpenSLESHelper.createRecord(&RecordCallback, nullptr, &AndroidSimpleBufferQueueCallback, nullptr);
    g_OpenSLESHelper.enqueueRecord(g_buffer, g_bufSize);
    g_OpenSLESHelper.setRecordState(SL_RECORDSTATE_RECORDING);
}

void stopRecord(){
    g_exit = true;
    g_cv.notify_one();
    g_OpenSLESHelper.setRecordState(SL_RECORDSTATE_STOPPED);
    g_OpenSLESHelper.destroyRecord();
    g_OpenSLESHelper.destroy();
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