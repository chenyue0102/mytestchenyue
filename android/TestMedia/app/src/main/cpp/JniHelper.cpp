//
// Created by chenyue on 2020/2/2.
//
#include <assert.h>
#include "JniHelper.h"

namespace JniHelper{
    jobject newObject(JNIEnv *env, jclass jclass1) {
        jobject jobject1 = nullptr;

        do{
            jmethodID jmethodId = env->GetMethodID(jclass1, "<init>", "()V");
            if (nullptr == jmethodId){
                assert(false);
                break;
            }
            if (nullptr == (jobject1 = env->NewObject(jclass1, jmethodId))){
                assert(false);
                break;
            }
        }while (false);
        return jobject1;
    }

    jobject newObject(JNIEnv *env, jclass jclass1, const char*sig, ...){
        jobject jobject1 = nullptr;

        do{
            jmethodID jmethodId = env->GetMethodID(jclass1, "<init>", sig);
            if (nullptr == jmethodId){
                assert(false);
                break;
            }
            va_list argp;
            va_start(argp, sig);
            jobject1 = env->NewObjectV(jclass1, jmethodId, argp);
            va_end(argp);
            if (nullptr == jobject1){
                assert(false);
                break;
            }
        }while(false);
        return jobject1;
    }

    Jstring2string::Jstring2string(JNIEnv *_env, jstring _jstring1) :env(_env),jstring1(_jstring1),str(nullptr){
        str = env->GetStringUTFChars(jstring1, nullptr);
    }

    Jstring2string::~Jstring2string() {
        Release();
    }

    const char *Jstring2string::getStr() throw(int){
        if (nullptr == str){
            throw -1;
        }
        return str;
    }

    Jstring2string::operator const char *() throw(int){
        return getStr();
    }

    void Jstring2string::Release() {
        if (nullptr != str){
            env->ReleaseStringUTFChars(jstring1, str);
            str = nullptr;
        }
    }

    stringbuild2string::stringbuild2string(JNIEnv *_env, jobject stringbuilder) :env(_env), jstring2String(nullptr){
        LocalObjectHolder<jclass> jclassStringBuilder(env, env->GetObjectClass(stringbuilder));
        jmethodID jmethodId = env->GetMethodID(jclassStringBuilder.getObject(), "toString", "()Ljava/lang/String;");
        if (nullptr != jmethodId){
            jstring2String = new Jstring2string(env, static_cast<jstring>(env->CallObjectMethod(stringbuilder, jmethodId)));
        }else{
            assert(false);
        }
    }

    stringbuild2string::~stringbuild2string() {
        Release();
    }

    void stringbuild2string::Release() {
        if (nullptr != jstring2String){
            delete jstring2String;
            jstring2String = nullptr;
        }
    }

    const char *stringbuild2string::getStr() throw(int) {
        if (nullptr != jstring2String){
            return jstring2String->getStr();
        }else{
            throw -1;
            return nullptr;
        }
    }

    stringbuild2string::operator const char *() throw(int) {
        return getStr();
    }
}