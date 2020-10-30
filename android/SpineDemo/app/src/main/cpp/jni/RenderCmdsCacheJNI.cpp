//
// Created by EDZ on 2020/10/29.
//
#include <jni.h>
#include "ShareData.h"
#include "Single.h"
#include "Log.h"
#include "RenderCmdsCache.h"
#include "JniHelper.h"
#include "MacroDefine.h"


extern "C"
JNIEXPORT jlong JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_new_1RenderCmdsCache(JNIEnv *env, jclass clazz) {
    RenderCmdsCache *renderCmdsCache = new RenderCmdsCache();
    jlong id = reinterpret_cast<jlong >(renderCmdsCache);
    ShareData::instance().insertRenderCmdsCache(id, renderCmdsCache);
    return id;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_delete_1RenderCmdsCache(JNIEnv *env, jclass clazz,
                                                                      jlong swig_cptr) {
    RenderCmdsCache *renderCmdsCache = ShareData::instance().removeRenderCmdsCache(swig_cptr);
    if (nullptr != renderCmdsCache){
        delete renderCmdsCache;
    }else{
        Log::e("delete render failed");
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_initShaderProgram(JNIEnv *env, jclass clazz,
                                                                jlong swig_cptr, jstring v_texture,
                                                                jstring f_texture, jstring v_color,
                                                                jstring f_color) {
    try{
        GETRENDER(swig_cptr);
        JniHelper::Jstring2string vTexture(env, v_texture), fTexture(env, f_texture), vColor(env, v_color), fColor(env, f_color);
        renderCmdsCache->initShaderProgram(vTexture.getStr(), fTexture.getStr(), vColor.getStr(), fColor.getStr());
    }catch(...){
        Log::e("Render exception fun:%s", __FUNCTION__);
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_setViewSize(JNIEnv *env, jclass clazz,
                                                          jlong swig_cptr, jfloat width,
                                                          jfloat height) {
    try{
        GETRENDER(swig_cptr);
        renderCmdsCache->setViewSize(MySize(width, height));
    }catch(...){
        Log::e("Render exception fun:%s", __FUNCTION__);
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_render(JNIEnv *env, jclass clazz, jlong swig_cptr) {
    try{
        GETRENDER(swig_cptr);
        renderCmdsCache->render();
    }catch(...){
        Log::e("Render exception fun:%s", __FUNCTION__);
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_RenderCmdsCacheJNI_clearCache(JNIEnv *env, jclass clazz,
                                                         jlong swig_cptr) {
    try{
        GETRENDER(swig_cptr);
        renderCmdsCache->clearCache();
    }catch(...){
        Log::e("Render exception fun:%s", __FUNCTION__);
        assert(false);
    }
}