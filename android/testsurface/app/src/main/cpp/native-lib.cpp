#include <jni.h>
#include <string>
#include <assert.h>
#include <GLES3/gl3.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraError.h>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraMetadataTags.h>
#include <camera/NdkCameraMetadata.h>
#include "OpenGLHelper.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_test_testsurface_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

GLuint g_program;
GLuint g_buffer;
GLuint g_vertex;
const char *g_vString = R"(
#version 300 es
in vec3 vertexPosition;
void main(){
gl_Position = vec4(vertexPosition, 1.0f);
}
)";
const char *g_fString = R"(
#version 300 es
precision mediump float;
out vec4 fColor;
void main(){
fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

extern "C"
JNIEXPORT void JNICALL
Java_com_test_testsurface_MyNDKGLRender_init(JNIEnv *env, jobject thiz) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    g_program = glCreateProgram();
    GLenum err = OpenGLHelper::attachShader(g_program, GL_VERTEX_SHADER, g_vString, 0);
    assert(err == GL_NO_ERROR);
    err = OpenGLHelper::attachShader(g_program, GL_FRAGMENT_SHADER, g_fString, 0);
    assert(err == GL_NO_ERROR);
    glLinkProgram(g_program);
    CHECKERR();

    GLfloat vertex[] = {
            -0.5f, -0.5f, 1.0f,
            0.5f, -0.5f, 1.0f,
            -0.5f, 0.5f, 1.0f,
            0.5f, 0.5f, 1.0f,
    };

    glGenBuffers(1, &g_buffer);CHECKERR();
    glBindBuffer(GL_ARRAY_BUFFER, g_buffer);CHECKERR();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &g_vertex);
    glBindVertexArray(g_vertex);
    GLuint vertexPositionLocation = glGetAttribLocation(g_program, "vertexPosition");
    glBindBuffer(GL_ARRAY_BUFFER, g_buffer);
    glVertexAttribPointer(vertexPositionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexPositionLocation);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}extern "C"
JNIEXPORT void JNICALL
Java_com_test_testsurface_MyNDKGLRender_surfaceChanged(JNIEnv *env, jobject thiz, jint width,
                                                       jint height) {
    glViewport(0, 0, width, height);
}extern "C"
JNIEXPORT void JNICALL
Java_com_test_testsurface_MyNDKGLRender_drawFrame(JNIEnv *env, jobject thiz) {
    glUseProgram(g_program);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(g_vertex);CHECKERR();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);CHECKERR();
    glFlush();

    glBindVertexArray(0);
    glUseProgram(0);
}
#if 0
ACameraManager *g_cameraManager = nullptr;
ACameraIdList *g_ACameraIdList = nullptr;
std::string g_cameraId;
static void EnumerateCamera(){
    camera_status_t status = ACameraManager_getCameraIdList(g_cameraManager, &g_ACameraIdList);
    assert(status == ACAMERA_OK);

    bool bContinue = true;
    for (int i = 0; i < g_ACameraIdList->numCameras && bContinue; i++){
        ACameraMetadata *cameraMetadata = nullptr;
        status = ACameraManager_getCameraCharacteristics(g_cameraManager, g_ACameraIdList->cameraIds[i], &cameraMetadata);
        assert(status == ACAMERA_OK);
        int32_t count = 0;
        const uint32_t *tags = nullptr;
        status = ACameraMetadata_getAllTags(cameraMetadata, &count, &tags);
        assert(status == ACAMERA_OK);
        for (int tagIdx = 0; tagIdx < count; tagIdx++){
            if (ACAMERA_LENS_FACING == tags[tagIdx]){
                ACameraMetadata_const_entry lensInfo = {0};
                status = ACameraMetadata_getConstEntry(cameraMetadata, tags[tagIdx], &lensInfo);
                assert(status == ACAMERA_OK);
                acamera_metadata_enum_android_lens_facing_t facing = static_cast<acamera_metadata_enum_android_lens_facing_t>(lensInfo.data.u8[0]);
                if (facing == ACAMERA_LENS_FACING_BACK){
                    g_cameraId = g_ACameraIdList->cameraIds[i];
                    bContinue = false;
                    break;
                }
            }
        }

        ACameraMetadata_free(cameraMetadata);
        cameraMetadata = nullptr;
    }

    ACameraManager_deleteCameraIdList(g_ACameraIdList);
    g_ACameraIdList = nullptr;
}
#endif
extern "C"
JNIEXPORT void JNICALL
Java_com_test_testsurface_MainActivity_createCamera(JNIEnv *env, jobject thiz) {
    //g_cameraManager = ACameraManager_create();
    //ACameraManager_openCamera(g_cameraManager, )
}

#include <memory>
#include <oboe/Oboe.h>
FILE *g_file = 0;

class MyAudioStreamCallback : public oboe::AudioStreamCallback{
public:
    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override {
        fwrite(audioData, 1, numFrames * audioStream->getChannelCount() * sizeof(int16_t), g_file);
        return oboe::DataCallbackResult::Continue;
    }
};

MyAudioStreamCallback *g_MyAudioStreamCallback = new MyAudioStreamCallback();
std::shared_ptr<oboe::AudioStream> g_AudioStream;

static void JNICALL recordAudio(JNIEnv *env, jobject thiz, jint devicdeId, jstring str){
    jboolean isCopy = false;
    const char *filePath = env->GetStringUTFChars(str, &isCopy);
    g_file = fopen(filePath, "wb");
    env->ReleaseStringUTFChars(str, filePath);

    oboe::AudioStreamBuilder builder;
    builder.setAudioApi(oboe::AudioApi::Unspecified)
        //->setFormat(oboe::AudioFormat::Float)//float need sdk >= 23
            ->setFormat(oboe::AudioFormat::I16)
        ->setSharingMode(oboe::SharingMode::Exclusive)
        ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
        ->setDeviceId(devicdeId)
        ->setDirection(oboe::Direction::Input)
        ->setChannelCount(2)
        ->setSampleRate(44100)
        ->setCallback(g_MyAudioStreamCallback);

    oboe::Result result = builder.openStream(g_AudioStream);
    assert(oboe::Result::OK == result);
    result = g_AudioStream->requestStart();
    assert(oboe::Result::OK == result);

    return;
}

static void JNICALL stopRecordAudio(JNIEnv *env, jobject thiz){
    if (g_AudioStream){
        g_AudioStream->stop(0);
        g_AudioStream->close();
        g_AudioStream.reset();
    }
    if (0 != g_file){
        fclose(g_file);
        g_file = 0;
    }
}
class MyOutputAudioStreamCallback : public oboe::AudioStreamCallback{

public:
    oboe::DataCallbackResult
    onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override {
        memset(audioData, 0, numFrames * sizeof(int16_t));

        int readCount = numFrames * sizeof(int16_t) * audioStream->getChannelCount();
        int size = fread(audioData, 1, readCount, g_file);
        if (size < readCount){
            audioStream->requestStop();
            return oboe::DataCallbackResult::Stop;
        }else{
            return oboe::DataCallbackResult::Continue;
        }
    }
};

MyOutputAudioStreamCallback *g_MyOutputAudioStreamCallback = new MyOutputAudioStreamCallback();
std::shared_ptr<oboe::AudioStream> g_outputstream;
static void JNICALL playAudio(JNIEnv *env, jobject thiz, jint devideId, jstring str){
    jboolean isCopy = false;
    const char *filePath = env->GetStringUTFChars(str, &isCopy);
    g_file = fopen(filePath, "rb");
    env->ReleaseStringUTFChars(str, filePath);

    oboe::AudioStreamBuilder builder;
    builder.setAudioApi(oboe::AudioApi::Unspecified)
        ->setFormat(oboe::AudioFormat::I16)
        ->setSharingMode(oboe::SharingMode::Exclusive)
        ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
        ->setDeviceId(devideId)
        ->setDirection(oboe::Direction::Output)
        ->setSampleRate(44100)
        ->setChannelCount(2)
        ->setCallback(g_MyOutputAudioStreamCallback);

    oboe::Result result = builder.openStream(g_outputstream);
    assert(result == oboe::Result::OK);
    int32_t framesPerBurst = g_outputstream->getFramesPerBurst();
    g_outputstream->setBufferSizeInFrames(framesPerBurst);
    result = g_outputstream->requestStart();
    assert(result == oboe::Result::OK);
}

static void JNICALL stopPlayAudio(JNIEnv *env, jobject thiz){
    if (g_outputstream){
        g_outputstream->stop(0);
        g_outputstream->close();
        g_outputstream.reset();
    }
    if (0 != g_file){
        fclose(g_file);
        g_file = 0;
    }
}
ACameraDevice_StateCallbacks g_stateCallbacks;
ACameraDevice *g_ACameraDevice = 0;
ACaptureRequest *g_ACaptureRequest = 0;
ACaptureSessionOutputContainer *g_ACaptureSessionOutputContainer = 0;
ACameraCaptureSession_stateCallbacks g_ACameraCaptureSession_stateCallbacks;
void my_ACameraDevice_StateCallback(void* context, ACameraDevice* device){

}

void my_ACameraDevice_ErrorStateCallback(void* context, ACameraDevice* device, int error){

}

void my_ACameraCaptureSession_stateCallback_onReady(void* context, ACameraCaptureSession *session){

}

void my_ACameraCaptureSession_stateCallback_onActive(void* context, ACameraCaptureSession *session){

}
void my_ACameraCaptureSession_stateCallback_onClosed(void* context, ACameraCaptureSession *session){

}

#include "Camera2.h"
#include "ImageReaderHelper.h"
#include "Log.h"

Camera2 *g_Camera2 = 0;


class MyImageReaderHelper : public ImageReaderHelper{
public:
    MyImageReaderHelper(const char *filePath){
        file = fopen(filePath, "wb");
        assert(0 != file);
    }
    ~MyImageReaderHelper(){
        fclose(file);
    }
protected:
    virtual void onImageCallback(int format, int32_t width, int32_t height, ImageData *images, int imageCount)override{
        fwrite(images[0].data, 1, width * height, file);
        u.resize(width * height /4);
        v.resize(width * height / 4);
        for (int i = 0;i < width * height / 4; i++){
            u[i] = images[1].data[i * 2];
        }
        for (int i = 0;i < width * height / 4; i++){
            v[i] = images[2].data[i * 2];
        }
        fwrite(u.data(), 1, u.size(), file);
        fwrite(v.data(), 1, v.size(), file);
    }
private:
    FILE *file;
    std::vector<uint8_t> u, v;
};
MyImageReaderHelper *g_ImageReaderHelper = 0;
static void JNICALL recordVideo(JNIEnv *env, jobject thiz, jstring jstring_cameraId, jint templateId, jstring jstring_save_file_path){
    jboolean isCopy = 0;
    const char *cameraId = env->GetStringUTFChars(jstring_cameraId, &isCopy);
    const char *filePath = env->GetStringUTFChars(jstring_save_file_path, &isCopy);

    //bool isSupport = Camera2::isSupportCamera2();
    //Log::e("recordVideo %s camera2", isSupport ? "support" : "not support");

    //CameraConfig cameraConfig = Camera2::getCameraConfig();

    //640 480
    g_Camera2 = new Camera2();
    g_Camera2->openCamera(cameraId);

    g_ImageReaderHelper = new MyImageReaderHelper(filePath);
    g_ImageReaderHelper->setSize(640, 480);
    g_ImageReaderHelper->setFormat(AIMAGE_FORMAT_YUV_420_888);
    g_ImageReaderHelper->create();

    g_Camera2->addSurface(TEMPLATE_PREVIEW, g_ImageReaderHelper->getNativeWindow());
    g_Camera2->start();

    env->ReleaseStringUTFChars(jstring_cameraId, cameraId);
    env->ReleaseStringUTFChars(jstring_save_file_path, filePath);
}

static void JNICALL startPreview(JNIEnv *env, jobject thiz){

}

static void JNICALL stopRecordVideo(JNIEnv *env, jobject thiz){
    g_Camera2->closeCamera();
    delete g_Camera2;
    g_Camera2 = 0;
    g_ImageReaderHelper->destroy();
    delete g_ImageReaderHelper;
    g_ImageReaderHelper = 0;
}

JNINativeMethod g_methods[] = {
        {"recordAudio", "(ILjava/lang/String;)V", (void*)&recordAudio},
        {"stopRecordAudio", "()V", (void*)&stopRecordAudio},
        {"playAudio", "(ILjava/lang/String;)V", (void*)&playAudio},
        {"stopPlayAudio", "()V", (void*)&stopPlayAudio},
        {"recordVideo", "(Ljava/lang/String;ILjava/lang/String;)V", (void*)&recordVideo},
        {"stopRecordVideo", "()V", (void*)&stopRecordVideo},
};

JavaVM *g_vm = 0;
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved){
    g_vm = vm;

    JNIEnv *env = 0;
    if (JNI_OK == (vm->GetEnv((void**)&env, JNI_VERSION_1_4))){
        jclass clazz = (*env).FindClass("com/test/testsurface/MainActivity");
        if (JNI_OK != (*env).RegisterNatives(clazz, g_methods, sizeof(g_methods) / sizeof(g_methods[0]))){
            assert(false);
        }
    }

    return JNI_VERSION_1_4;
}