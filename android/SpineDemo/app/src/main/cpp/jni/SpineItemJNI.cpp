#include <jni.h>
#include <string>
#include "SpineItem.h"
#include "ShareData.h"
#include "JniHelper.h"
#include "Single.h"
#include "Log.h"
#include "MacroDefine.h"


extern "C"
JNIEXPORT jlong JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_new_1SpineItem(JNIEnv *env, jclass clazz) {
    SpineItem *spineItem = new SpineItem();
    jlong id = reinterpret_cast<jlong>(spineItem);
    ShareData::instance().insertSpineItem(id, spineItem);
    return id;
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_delete_1SpineItem(JNIEnv *env, jclass clazz,
                                                          jlong swig_cptr) {
    SpineItem *spineItem = ShareData::instance().removeSpineItem(swig_cptr);
    if (nullptr != spineItem){
        delete spineItem;
    }else{
        Log::e("delete spine failed");
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_setAtlasFile(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                     jstring file_path) {
    try{
        JniHelper::Jstring2string jstring2String = JniHelper::Jstring2string(env, file_path);
        GETSPINEITEM(swig_cptr);
        spineItem->setAtlasFile(jstring2String.getStr());
    }catch (...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_setSkeletonFile(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                        jstring file_path) {
    try{
        JniHelper::Jstring2string jstring2String = JniHelper::Jstring2string(env, file_path);
        GETSPINEITEM(swig_cptr);
        spineItem->setSkeletonFile(jstring2String.getStr());
    }catch (...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_create(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                               jlong texture_loader_swig_cptr) {
    bool ret = false;
    try{
        GETSPINEITEM(swig_cptr);
        GETTEXTURELOADER(texture_loader_swig_cptr);
        ret = spineItem->create(textureLoader);
    }catch (...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_setAnimation(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                     jint track_index, jstring name,
                                                     jboolean loop) {
    try{
        JniHelper::Jstring2string jstring2String = JniHelper::Jstring2string(env, name);
        GETSPINEITEM(swig_cptr);
        spineItem->setAnimation(track_index, jstring2String.getStr(), loop);
    }catch (...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
}extern "C"
JNIEXPORT jlong JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_getSkeleton(JNIEnv *env, jclass clazz, jlong swig_cptr) {
    jlong ret = 0;
    try{
        GETSPINEITEM(swig_cptr);
        ret = swig_cptr;//用SpineItem的指针
    }catch (...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_updateSkeletonAnimation(JNIEnv *env, jclass clazz,
                                                                jlong swig_cptr, jfloat delta) {
    try{
        GETSPINEITEM(swig_cptr);
        spineItem->updateSkeletonAnimation(delta);
    }catch(...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SpineItemJNI_renderToCache(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                      jlong swig_cptr_render) {
    try{
        GETSPINEITEM(swig_cptr);
        GETRENDER(swig_cptr_render);
        spineItem->batchRenderCmd();
        spineItem->renderToCache(renderCmdsCache);
    }catch(...){
        Log::e("SpineItem exception fun:%s", __FUNCTION__);
        assert(false);
    }
}