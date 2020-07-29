package com.test.testsurface;

import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLRender implements GLSurfaceView.Renderer {
    private int mProgram;
    private int []mBuffers = new int[1];
    private int []mVertexArray = new int[1];
    private static final String VERTEX_STRING =
            "#version 300 es\n" +
            "in vec3 vertexPosition;\n" +
            "void main(){\n" +
            "gl_Position = vec4(vertexPosition, 1.0f);\n" +
            "}";

    private static final String FRAGMENT_STRING =
            "#version 300 es\n" +
            "precision mediump float;\n" +
            "out vec4 fColor;\n" +
            "void main(){\n" +
                    "fColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n" +
            "}";
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES30.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        mProgram = GLES30.glCreateProgram();
        int ret = OpenGLHelper.attachShader(mProgram, GLES30.GL_VERTEX_SHADER, VERTEX_STRING);
        if (ret != GLES30.GL_NO_ERROR){
            Log.i("MyGLRender", "attachShader failed");
        }
        ret = OpenGLHelper.attachShader(mProgram, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_STRING);
        GLES30.glLinkProgram(mProgram);
        OpenGLHelper.outputProgramLog(mProgram);

        float vertex[] = new float[]{
                -0.5f, -0.5f, 1.0f,
                0.5f, -0.5f, 1.0f,
                -0.5f, 0.5f, 1.0f,
                0.5f, 0.5f, 1.0f,
        };

        try{
            GLES30.glGenBuffers(1, mBuffers, 0);
            OpenGLHelper.checkError();
            GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, mBuffers[0]);
            OpenGLHelper.checkError();
            GLES30.glBufferData(GLES30.GL_ARRAY_BUFFER, 4 * vertex.length, FloatBuffer.wrap(vertex), GLES30.GL_STATIC_DRAW);
            OpenGLHelper.checkError();
            GLES30.glGenVertexArrays(1, mVertexArray, 0);
            OpenGLHelper.checkError();
            GLES30.glBindVertexArray(mVertexArray[0]);
            OpenGLHelper.checkError();
            GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, mBuffers[0]);
            OpenGLHelper.checkError();
            int vertexAttribLocation = GLES30.glGetAttribLocation(mProgram, "vertexPosition");
            GLES30.glVertexAttribPointer(vertexAttribLocation, 3, GLES30.GL_FLOAT, false, 0, 0);
            GLES30.glEnableVertexAttribArray(vertexAttribLocation);
            OpenGLHelper.checkError();

            GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, 0);
            GLES30.glBindVertexArray(0);
        }catch (OpenGLHelper.MyException e){
            e.printStackTrace();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES30.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        try{
            GLES30.glUseProgram(mProgram);
            GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT);
            OpenGLHelper.checkError();

            GLES30.glBindVertexArray(mVertexArray[0]);
            OpenGLHelper.checkError();
            GLES30.glDrawArrays(GLES30.GL_TRIANGLE_STRIP, 0, 4);
            OpenGLHelper.checkError();
            GLES30.glFlush();
            OpenGLHelper.checkError();

            GLES30.glBindVertexArray(0);
            GLES30.glUseProgram(0);
        }catch (OpenGLHelper.MyException e){
            e.printStackTrace();
        }

    }
}
