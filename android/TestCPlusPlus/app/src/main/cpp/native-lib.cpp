#include <jni.h>
#include <string>

std::string jstring2string(JNIEnv *env, jstring s){
    std::string str;
    const char *pstr = env->GetStringUTFChars(s, 0);
    if (0 != pstr){
        str = pstr;
        env->ReleaseStringUTFChars(s, pstr);
    }
    return str;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_testcplusplus_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "stringFromJNI";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_testcplusplus_MainActivity_stringFromJNI2(JNIEnv *env, jclass clazz) {
    std::string hello = "stringFromJNI2";
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT jint JNICALL
Java_com_example_testcplusplus_MainActivity_string2Int(JNIEnv *env, jobject thiz, jstring s) {
    jint ret = 0;
    jboolean iscopy=0;
    //将java字符串转换成c字符串
    const char*  str = env->GetStringUTFChars(s, &iscopy);
    if (0 != str){
        ret = atoi(str);
        env->ReleaseStringUTFChars(s, str);
    }
    return ret;
}extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_testcplusplus_MainActivity_getTop3(JNIEnv *env, jobject thiz, jintArray i) {
    jintArray retArray;
    retArray = env->NewIntArray(3);
    if (0 != retArray){
        jsize length = env->GetArrayLength(i);
        int count = std::min(length, 3);
#if 0
        jint *inputArray = new jint[length];
        env->GetIntArrayRegion(i, 0, length, inputArray);
        env->SetIntArrayRegion(retArray, 0, count, inputArray);
        delete []inputArray;
#else
        jboolean iscopy = 0;
        jint *nativeArray = env->GetIntArrayElements(i, &iscopy);
        if (0 != nativeArray){
            env->SetIntArrayRegion(retArray, 0, count, nativeArray);
            //JNI_ABORT 释放原生数组,不用将内容拷贝回去
            //JNI_COMMIT 将内容拷贝回去,不释放数组,用于周期更新内容
            //0 内容拷贝回去,并释放数组
            env->ReleaseIntArrayElements(i, nativeArray, JNI_ABORT);
        }
#endif
    }
    return retArray;
}extern "C"

char *g_str = 0;

extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_testcplusplus_MainActivity_getDirectBuffer(JNIEnv *env, jobject thiz) {
    char *str = (char*)malloc(1024);
    g_str = str;
    strcpy(str, "hello, directbuffer");
    jobject byteBuffer = env->NewDirectByteBuffer(str, 1024);
    return byteBuffer;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_releaseDirectBuffer(JNIEnv *env, jobject thiz,
                                                                jobject b) {
    char *str = (char*)env->GetDirectBufferAddress(b);
    jlong length = env->GetDirectBufferCapacity(b);
    if (str == g_str){
        free(str);
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_testAccessField(JNIEnv *env, jobject thiz) {
    jclass clazz = env->GetObjectClass(thiz);
    jfieldID instanceFieldId = env->GetFieldID(clazz, "instanceField", "Ljava/lang/String;");
    jfieldID staticFieldId = env->GetStaticFieldID(clazz, "staticField", "Ljava/lang/String;");
    jstring str1= (jstring)env->GetObjectField(thiz, instanceFieldId);
    jstring str2 = (jstring)env->GetStaticObjectField(clazz, staticFieldId);
    std::string s1 = jstring2string(env, str1);
    std::string s2 = jstring2string(env, str2);

    jmethodID test1 = env->GetMethodID(clazz, "test1", "([I[I)I");
    return;
}