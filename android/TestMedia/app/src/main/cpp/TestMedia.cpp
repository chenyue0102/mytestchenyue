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
#include "JniHelper.h"
#include "TaskPool.h"
#include "Mp3Player.h"

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

extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testmedia_TestMedia_playMp3File(JNIEnv *env, jobject thiz, jstring file) {
    try{
        JniHelper::Jstring2string str(env, file);
        std::string filePath = str.getStr();
        auto fun = [filePath](){
            Mp3Player *mp3Player = new Mp3Player();
            mp3Player->openFile(filePath.c_str());
            delete mp3Player;
        };
        g_TaskPool->AddTask(fun);
    }catch (...){

    }

    return 0;
}