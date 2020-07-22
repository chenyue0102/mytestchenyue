#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/system_properties.h>
#include <sys/socket.h>
#include <endian.h>
#include <linux/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <mutex>
#include <atomic>
#include "JniHelper.h"
#include "TaskPool.h"
#include "Mp3Player.h"
#include "OpenSLESHelper.h"
#include "LameHelper.h"
#include "RingQueue.h"
#include "MacroDefine.h"
#include "Log.h"
#include "Single.h"
#include "SystemTime.h"

__attribute__((constructor)) static void onDlOpen(void)
{
}

std::string jstring2string(JNIEnv *env, jstring s){
    std::string str;
    const char *pstr = env->GetStringUTFChars(s, 0);
    if (0 != pstr){
        str = pstr;
        env->ReleaseStringUTFChars(s, pstr);
    }
    return str;
}
JavaVM *g_JavaVM = 0;
CTaskPool * g_TaskPool = NULL;

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved){
    g_JavaVM = vm;
    __android_log_write(ANDROID_LOG_DEBUG, "JNI", "JNI_OnLoad");
    g_TaskPool = new CTaskPool();
    g_TaskPool->Open(5);
    return JNI_VERSION_1_4;
}
Mp3Player *g_Mp3Player = 0;
OpenSLESHelper *g_OpenSLESHelper = nullptr;
LameHelper *g_LameHelper = nullptr;
RingQueue *g_RingQueue = nullptr;
std::mutex g_mutex;
std::condition_variable g_cv;
std::atomic<bool> g_needCallMediaCallback;
SystemTime *g_SystemTime = nullptr;

void SLAPIENTRY mediaCallback(SLAndroidSimpleBufferQueueItf caller, void *pContext){
    if (nullptr != caller){
        auto timePoint1 = g_SystemTime->getCurrentTimeMs();
        if (g_RingQueue->getDataSize() > 0){
            const int bufLen = 44100 * 2 * 2;
            unsigned char buf[bufLen];
            int getSize = g_RingQueue->get(buf, bufLen);
            if (getSize > 0){
                SC(Log).d("mediaCallback Enqueue size:%d", getSize);
                auto timePoint2 = g_SystemTime->getCurrentTimeMs();
                SC(Log).e("mediaCallback time:%lld", timePoint2 - timePoint1);
                (*caller)->Enqueue(caller, buf, getSize);
            }else{
                SC(Log).d("mediaCallback g_RingQueue->get empty");
            }
            std::lock_guard<std::mutex> lk(g_mutex);
            g_cv.notify_one();
            g_needCallMediaCallback = false;
        }else{
            SC(Log).d("mediaCallback need buffer");
            g_needCallMediaCallback = true;
        }
    }else{
        SC(Log).d("mediaCallback error");
    }
}

bool checkRead(){
    if (g_RingQueue->getFreeSize() >= 1152 * 2 * 2){
        return true;
    }else{
        return false;
    }
}

void readThread(std::string filePath){
    bool success = true;
    g_LameHelper = new LameHelper();
    g_LameHelper->open(filePath.c_str());
    while(success){
        std::unique_lock<std::mutex> lk(g_mutex);
        g_cv.wait(lk, &checkRead);
        lk.unlock();
        const int bufLen = 1152 * 2 * 2;
        while (g_RingQueue->getFreeSize() >= bufLen){
            unsigned char buf[bufLen];
            int readLen = g_LameHelper->decode(buf, bufLen);
            if (readLen > 0){
                g_RingQueue->put(buf, readLen);
                if (g_needCallMediaCallback){
                    mediaCallback(g_OpenSLESHelper->getBufferQueue(), nullptr);
                }
            } else{
                success = false;
                break;
            }
        }
    }
}

void testMedia(const std::string &filePath){
    SC(Log).setTag("testmedia");
    g_SystemTime = new SystemTime();
    g_RingQueue = new RingQueue(44100 * 2 * 2 * 2);
    g_OpenSLESHelper = new OpenSLESHelper();
    g_OpenSLESHelper->createEngine();
    g_OpenSLESHelper->createOutputMix();
    SLDataLocator_AndroidSimpleBufferQueue bufferQueue = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    SLDataFormat_PCM pcm = {
            SL_DATAFORMAT_PCM,
            2,
            SL_SAMPLINGRATE_44_1,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_PCMSAMPLEFORMAT_FIXED_16,
            SL_SPEAKER_FRONT_LEFT | SL_SPEAKER_FRONT_RIGHT,
            SL_BYTEORDER_LITTLEENDIAN,
    };
    SLDataSource slDataSource = {&bufferQueue, &pcm};
    SLDataLocator_OutputMix outputMix = {SL_DATALOCATOR_OUTPUTMIX, g_OpenSLESHelper->getOutputMixObject()};
    SLDataSink slDataSink = {&outputMix, nullptr};
    const SLInterfaceID ids[] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME};
    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
    g_OpenSLESHelper->createPlayer(slDataSource, slDataSink, 3, ids, req);
    g_OpenSLESHelper->registerBufferQueueCallback(&mediaCallback, nullptr);
    g_OpenSLESHelper->setPlayState(SL_PLAYSTATE_PLAYING);
    g_needCallMediaCallback = true;
    g_TaskPool->AddTask([filePath](){
        readThread(filePath.c_str());
    });
    //mediaCallback(g_OpenSLESHelper->getBufferQueue(), nullptr);
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testmedia_TestMedia_playMp3File(JNIEnv *env, jobject thiz, jstring file) {
    try{
        JniHelper::Jstring2string str(env, file);
        std::string filePath = str.getStr();
        auto fun = [filePath](){
            testMedia(filePath);
        };
        g_TaskPool->AddTask(fun);
    }catch (...){

    }

    return 0;
}