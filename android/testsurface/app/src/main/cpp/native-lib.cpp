#include <jni.h>
#include <string>
#include <assert.h>
#include <GLES3/gl3.h>
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