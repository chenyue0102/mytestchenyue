//
// Created by chenyue on 2020/2/2.
//

#ifndef KSTVCASTSCREEN_JNIHELPER_H
#define KSTVCASTSCREEN_JNIHELPER_H
#include <jni.h>

#define LOG_DEBUG(tag,text) \
    __android_log_write(ANDROID_LOG_DEBUG, tag, text)

#define LOG_INFO(tag,text) \
    __android_log_write(ANDROID_LOG_INFO, tag, text)

#define LOG_WARN(tag,text) \
    __android_log_write(ANDROID_LOG_WARN, tag, text)

namespace JniHelper {
jobject newObject(JNIEnv *env, jclass jclass1);
jobject newObject(JNIEnv *env, jclass jclass1, const char*sig, ...);

template<typename T>
class LocalObjectHolder{
public:
    LocalObjectHolder(JNIEnv *_env, T _obj): env(_env), obj(_obj){
        if (nullptr == obj){
            throw -1;
        }
    }
    ~LocalObjectHolder(){
        Release();
    }

    T getObject() throw(int){
        if (nullptr == obj){
            throw -1;
        }
        return obj;
    }

    operator T() throw(int){
        return getObject();
    }

    void Release(){
        if (nullptr != obj){
            env->DeleteLocalRef(obj);
            obj = nullptr;
        }
    }

private:
    JNIEnv *env;
    T obj;
};

//必须保证jstring有效
class Jstring2string{
public:
    Jstring2string(JNIEnv *_env, jstring _jstring1);
   ~Jstring2string();

public:
    const char* getStr() throw(int);

    operator const char*()throw(int);

    void Release();

private:
    const char *str;
    JNIEnv *env;
    jstring jstring1;
};

class stringbuild2string{
public:
    stringbuild2string(JNIEnv *_env, jobject stringbuilder);
    ~stringbuild2string();

public:
    void Release();

    const char* getStr() throw(int);

    operator const char*()throw(int);
private:
    JNIEnv *env;
    Jstring2string *jstring2String;
};
};


#endif //KSTVCASTSCREEN_JNIHELPER_H
