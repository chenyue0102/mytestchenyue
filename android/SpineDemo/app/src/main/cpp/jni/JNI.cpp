#include <jni.h>
#include <assert.h>
#include <string>
#include <android/log.h>
#include "ShareData.h"
#include "Single.h"
#include "Log.h"

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved){
    ShareData::instance().setJavaVM(vm);
    Log::d("JNI_OnLoad");
    return JNI_VERSION_1_4;
}
