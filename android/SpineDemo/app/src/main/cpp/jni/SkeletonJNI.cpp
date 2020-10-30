//
// Created by EDZ on 2020/10/29.
//
#include <jni.h>
#include "ShareData.h"
#include "Single.h"
#include "Log.h"
#include "SpineItem.h"
#include "MacroDefine.h"



extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SkeletonJNI_setPositon(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                  jfloat x, jfloat y) {
    try{
        GETSKELETON(swig_cptr);
        skeleton->setPosition(x, y);
    }catch (...){
        Log::e("Skeleton exception fun:%s", __FUNCTION__);
        assert(false);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SkeletonJNI_setScaleX(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                 jfloat scale_x) {
    try{
        GETSKELETON(swig_cptr);
        skeleton->setScaleX(scale_x);
    }catch (...){
        Log::e("Skeleton exception fun:%s", __FUNCTION__);
        assert(false);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SkeletonJNI_setScaleY(JNIEnv *env, jclass clazz, jlong swig_cptr,
                                                 jfloat scale_y) {
    try{
        GETSKELETON(swig_cptr);
        skeleton->setScaleY(scale_y);
    }catch (...){
        Log::e("Skeleton exception fun:%s", __FUNCTION__);
        assert(false);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ksstory_spinewrap_SkeletonJNI_updateWorldTransform(JNIEnv *env, jclass clazz,
                                                            jlong swig_cptr) {
    try{
        GETSKELETON(swig_cptr);
        skeleton->updateWorldTransform();
    }catch (...){
        Log::e("Skeleton exception fun:%s", __FUNCTION__);
        assert(false);
    }
}