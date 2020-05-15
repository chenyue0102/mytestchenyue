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
#include "Platinum.h"

#define LOG_DEBUG(tag,text) \
    __android_log_write(ANDROID_LOG_DEBUG, tag, text)

/*----------------------------------------------------------------------
|   logging
+---------------------------------------------------------------------*/
NPT_SET_LOCAL_LOGGER("platinum.android.jni")

/*----------------------------------------------------------------------
|   functions
+---------------------------------------------------------------------*/
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
extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved){
    g_JavaVM = vm;
    __android_log_write(ANDROID_LOG_DEBUG, "JNI", "JNI_OnLoad");
    //NPT_LogManager::GetDefault().Configure("plist:.level=FINE;.handlers=ConsoleHandler;.ConsoleHandler.outputs=2;.ConsoleHandler.colors=false;.ConsoleHandler.filter=59");
    return JNI_VERSION_1_4;
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

    jmethodID test1 = env->GetMethodID(clazz, "test1", "([I[Ljava/lang/String;[I)I");
    jmethodID  test2 = env->GetStaticMethodID(clazz, "test2", "([BII)Ljava/nio/ByteBuffer;");
    jintArray intArray1 = env->NewIntArray(1);
    int value1 = 1, value2 = 2;
    env->SetIntArrayRegion(intArray1, 0, 1, &value1);
    jintArray intArray2 = env->NewIntArray(1);
    env->SetIntArrayRegion(intArray2, 0, 1, &value2);
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray objArray1 = env->NewObjectArray(1, stringClass, 0);
    jboolean exception = env->ExceptionCheck();
    jint ret = env->CallIntMethod(thiz, test1, intArray1, objArray1, intArray2);
    exception = env->ExceptionCheck();
    //env->CallStaticBooleanMethod()
    env->DeleteLocalRef(clazz);
    env->DeleteLocalRef(intArray1);
    env->DeleteLocalRef(intArray2);

    return;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_callVoidMethod(JNIEnv *env, jobject thiz,
                                                           jboolean b_throw) {
    jclass clazz = env->GetObjectClass(thiz);
    jmethodID jmethodId = env->GetMethodID(clazz, "voidMethod", "()V");
    env->CallVoidMethod(thiz, jmethodId);
    jthrowable jthrowable1 = env->ExceptionOccurred();
    if (0 != jthrowable1){
        if (b_throw){
            env->ExceptionClear();
            jclass jclass1 = env->FindClass("java/io/IOException");
            if (0 != jclass1){
                env->ThrowNew(jclass1, "abcd");
            }
        }
        else{
            env->ExceptionClear();
        }
    }
}
jobject  g_stringClass = 0;
jweak g_stringWeak = 0;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_testRef(JNIEnv *env, jobject thiz) {
    jclass stringClass = env->FindClass("java/lang/String");
    g_stringClass = env->NewGlobalRef(stringClass);
    g_stringWeak = env->NewWeakGlobalRef(stringClass);
    if (JNI_FALSE == env->IsSameObject(g_stringWeak, NULL)){
        printf("ok");
    }
    env->DeleteLocalRef(stringClass);
    //env->DeleteWeakGlobalRef(g_stringWeak);

    //synchronized thiz
    if (JNI_OK == env->MonitorEnter(thiz)){

    }
    if (JNI_OK == env->MonitorExit(thiz)){

    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_testfile(JNIEnv *env, jobject thiz) {
    FILE *f = fopen("/sdcard/test.log", "w");
    const char *writeData = "write data";
    fwrite(writeData, 1, strlen(writeData), f);
    fclose(f);
}
pthread_t g_threadId = 0;

void test(){
    char value[PROP_VALUE_MAX] = {0};
    int r = __system_property_get("ro.product.model", value);
    if (r > 0){

    }
    const prop_info *pi = __system_property_find("ro.product.model");
    char name[PROP_NAME_MAX] = {0};
    char value2[PROP_VALUE_MAX] = {0};
    r = __system_property_read(pi, name, value2);

    int i = 0;
    while (0 != (pi = __system_property_find_nth(i++))){
        r = __system_property_read(pi, name, value);
        if (r > 0){
            std::string s = name;
            s += " ";
            s += value;
            LOG_DEBUG("JNI", s.c_str());
        }
    }

    uid_t uid = getuid();
    gid_t gid = getgid();
    char* logname = getlogin();
    LOG_DEBUG("JNI", logname);

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    if (0 != pthread_mutex_lock(&mutex)){
        LOG_DEBUG("JNI", "pthread_mutex_lock failed");
    }
    if (0 != pthread_mutex_unlock(&mutex)){
        LOG_DEBUG("JNI", "pthread_mutex_unlock failed");
    }
    if (0 != pthread_mutex_destroy(&mutex)){
        LOG_DEBUG("JNI", "pthread_mutex_destroy failed");
    }
}

void* threadProc(void *argument){
    JNIEnv *env = 0;
    jint ret = g_JavaVM->AttachCurrentThread(&env, 0);
    if (ret == JNI_OK){
        //ok
    }
    jobject jobject1 = (jobject)argument;
    jclass jclass1 = env->GetObjectClass(jobject1);
    jfieldID  jfieldId = env->GetFieldID(jclass1, "instanceField", "Ljava/lang/String;");
    env->DeleteLocalRef(jclass1);
    jstring jstring1 = (jstring)env->GetObjectField(jobject1, jfieldId);
    std::string sss = jstring2string(env, jstring1);
    char path[128] = {0};
    getcwd(path, 128);
    FILE *f = fopen("/data/data/com.example.testcplusplus/test.log", "w+");
    auto s = errno;
    fwrite(sss.c_str(), 1, sss.size(), f);
    fclose(f);

    test();
    env->DeleteGlobalRef(jobject1);
    g_JavaVM->DetachCurrentThread();
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_initThread(JNIEnv *env, jobject thiz) {
    jobject jobject1 = env->NewGlobalRef(thiz);
    if (0 == pthread_create(&g_threadId, 0, &threadProc, jobject1)){
        LOG_DEBUG("JNI", "create thread success");
    }
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_destroyThread(JNIEnv *env, jobject thiz) {
    void *ret = 0;
    pthread_join(g_threadId, &ret);
}

jobject g_instanceRef = 0;
jobject g_classLoader = 0;
class MediaRendererDelegate : public PLT_MediaRendererDelegate
{
public:
    virtual NPT_Result OnGetCurrentConnectionInfo(PLT_ActionReference& action)
    {
        return 0;
    }

    // AVTransport
    virtual NPT_Result OnNext(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnPause(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnPlay(PLT_ActionReference& action) {
        JNIEnv *env = 0;
        jint ret = g_JavaVM->AttachCurrentThread(&env, 0);
        if (ret == JNI_OK){
            //ok
            jclass loaderClass = env->GetObjectClass(g_classLoader);
            jmethodID jmethodId1 = env->GetMethodID(loaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
            jstring className = env->NewStringUTF("com/example/testcplusplus/MainActivity");
            jobject tmpObj = env->CallObjectMethod(g_classLoader, jmethodId1, className);
            //jclass jclass2 = tmpObj;
            //env->DeleteLocalRef(className);
#if 0
            jclass jclass1 = env->GetObjectClass(g_instanceRef);
            jmethodID jmethodId = env->GetMethodID(jclass1, "callbackFun", "(I)V");
#else
            jmethodID jmethodId = env->GetMethodID((jclass)tmpObj, "callbackFun", "(I)V");
#endif
            env->CallVoidMethod(g_instanceRef, jmethodId, 199);
            g_JavaVM->DetachCurrentThread();
        }
        return 0;
    }
    virtual NPT_Result OnPrevious(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnSeek(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnStop(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnSetAVTransportURI(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnSetPlayMode(PLT_ActionReference& action) {
        return 0;
    }

    // RenderingControl
    virtual NPT_Result OnSetVolume(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnSetVolumeDB(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnGetVolumeDBRange(PLT_ActionReference& action) {
        return 0;
    }
    virtual NPT_Result OnSetMute(PLT_ActionReference& action) {
        return 0;
    }
};


extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_testPlatinum(JNIEnv *env, jobject thiz) {
    g_instanceRef = env->NewGlobalRef(thiz);
    //g_instanceClass = env->FindClass("com/example/testcplusplus/MainActivity");
    //jmethodID jmethodId = env->GetMethodID(g_instanceClass, "callbackFun", "(I)V");
    PLT_UPnP* self = new PLT_UPnP();

    MediaRendererDelegate *p = new MediaRendererDelegate();
    PLT_MediaRenderer *mediaRenderer = new PLT_MediaRenderer("Platinum Media Renderer",
                                                             false,
                                                             "e6572b54-f3c7-2d91-2fb5-b757f2537e21");
    mediaRenderer->SetDelegate(p);
    PLT_DeviceHostReference device(mediaRenderer);
    self->AddDevice(device);
    self->Start();
    //delete self;
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_setClassLoader(JNIEnv *env, jobject thiz,
                                                           jobject my_class_loader) {
    g_classLoader = env->NewGlobalRef(my_class_loader);
}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_startServer(JNIEnv *env, jobject thiz) {

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_testcplusplus_MainActivity_testRawSocket(JNIEnv *env, jobject thiz) {
    int sock = -1;
    do{
        if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP)) == -1){
            assert(false);
            break;
        }
        std::string strSendData;
        strSendData.resize(sizeof(iphdr) + sizeof(udphdr), '\0');
    }while(false);
    if (-1 != sock){
        close(sock);
        sock = -1;
    }
}