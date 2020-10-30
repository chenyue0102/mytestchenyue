//
// Created by EDZ on 2020/10/30.
//

#include <jni.h>
#include "ShareData.h"
#include "Single.h"
#include "Log.h"
#include "MacroDefine.h"
#include "texture.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_ksstory_spinewrap_TextureLoaderJNI_new_1TextureLoader(JNIEnv *env, jclass clazz) {
    AimyTextureLoader *textureLoader = new AimyTextureLoader();
    jlong id = reinterpret_cast<jlong>(textureLoader);
    ShareData::instance().insertTextureLoader(id, textureLoader);
    return id;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_TextureLoaderJNI_delete_1TextureLoader(JNIEnv *env, jclass clazz,
                                                                  jlong swig_cptr) {
    AimyTextureLoader *textureLoader = ShareData::instance().removeTextureLoader(swig_cptr);
    if (nullptr != textureLoader){
        delete textureLoader;
    }else{
        Log::e("delete texture loader failed");
        assert(false);
    }
}
