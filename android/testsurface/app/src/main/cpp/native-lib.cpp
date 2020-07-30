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

extern "C"
JNIEXPORT void JNICALL
Java_com_test_testsurface_MainActivity_createCamera(JNIEnv *env, jobject thiz) {
    g_cameraManager = ACameraManager_create();
    ACameraManager_openCamera(g_cameraManager, )
}