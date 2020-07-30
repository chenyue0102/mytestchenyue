package com.test.testcamera;

import android.graphics.ImageFormat;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;

import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.FloatBuffer;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyYUVRender implements GLSurfaceView.Renderer {

    private static final String VERTEX = "#version 300 es\n" +
            "in vec3 vertexPosition;\n" +
            "in vec2 texturePosition;\n" +
            "out vec2 esTexturePosition;\n" +
            "void main(){\n" +
            "    gl_Position = vec4(vertexPosition, 1.0f);\n" +
            "    esTexturePosition = texturePosition;\n" +
            "}";

    private static final String FRAGMENT_NV21 = "#version 300 es\n" +
            "precision mediump float;\n" +
            "in vec2 esTexturePosition;\n" +
            "uniform sampler2D y_texture;\n" +
            "uniform sampler2D uv_texture;\n" +
            "out vec4 fColor;\n" +
            "void main() {\n" +
            "    vec3 yuv, uv, rgb;\n" +
            "    yuv.x = texture(y_texture, esTexturePosition).r;\n" +
            "    uv = texture(uv_texture, esTexturePosition).rgb;\n" +
            "    yuv.y = uv.r - 0.5f;\n" +
            "    yuv.z = uv.g - 0.5f;\n" +
            "    rgb = mat3(1.0, 1.0, 1.0,\n" +
            "    0.0, -0.39465, 2.03211,\n" +
            "    1.13983, -0.58060, 0.0) * yuv;\n" +
            "    fColor = vec4(rgb.rgb, 1.0f);\n" +
            "}";

    private static final float []vertexs = new float[]{
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            //texture position
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
    };

    private int mWidth;
    private int mHeight;
    private int mFormat;
    private int mProgram;
    private int []mBuffer = new int[1];
    private int []mVertexArray = new int[1];
    private int []mTextures = new int[3];
    private boolean mInit;
    private Lock mLock = new ReentrantLock();
    private ByteBuffer mYBuffer;
    private ByteBuffer mUVBuffer;
    private boolean mYUBBufferDirty;

    public MyYUVRender(){

    }

    public void setInfo(int width, int height, int format){
        try{
            mLock.lock();
            mWidth = width;
            mHeight = height;
            mFormat = format;
        }finally {
            mLock.unlock();
        }

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        try{
            mLock.lock();
            init();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            mLock.unlock();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        GLES30.glViewport(0, 0, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        try{
            mLock.lock();
            if (!mInit && mFormat != 0){
                init();
            }
            doDrawFrame();
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            mLock.unlock();
        }
    }

    private void doDrawFrame() throws Exception{
        if (!mInit){
            throw new Exception("");
        }
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT);
        GLES30.glUseProgram(mProgram);
        OpenGLHelper.checkError();

        if (mFormat == ImageFormat.NV21){
            if (mYUBBufferDirty){
                mYUBBufferDirty = false;
                GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, mTextures[0]);
                GLES30.glTexSubImage2D(GLES30.GL_TEXTURE_2D, 0, 0, 0, mWidth, mHeight, GLES30.GL_RED, GLES30.GL_UNSIGNED_BYTE, mYBuffer);
                GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, mTextures[1]);
                GLES30.glTexSubImage2D(GLES30.GL_TEXTURE_2D, 0, 0, 0, mWidth / 2, mHeight / 2, GLES30.GL_RG, GLES30.GL_UNSIGNED_BYTE, mUVBuffer);
                GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, 0);
            }

            GLES30.glActiveTexture(GLES30.GL_TEXTURE0);
            GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, mTextures[0]);
            int yTextureLocation = GLES30.glGetUniformLocation(mProgram, "y_texture");
            GLES30.glUniform1i(yTextureLocation, 0);

            GLES30.glActiveTexture(GLES30.GL_TEXTURE0 + 1);
            GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, mTextures[1]);
            int uvTextureLocation = GLES30.glGetUniformLocation(mProgram, "uv_texture");
            GLES30.glUniform1i(uvTextureLocation, 1);
        }else{
            throw new Exception("");
        }
        GLES30.glDrawArrays(GLES30.GL_TRIANGLE_STRIP, 0, 4);
        GLES30.glFlush();
        OpenGLHelper.checkError();

        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, 0);
        GLES30.glUseProgram(0);
    }

    private void init() throws Exception{
        if (0 == mFormat || 0 == mWidth || 0 == mHeight){
            throw new Exception("");
        }
        GLES30.glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        mProgram = GLES30.glCreateProgram();
        OpenGLHelper.checkError();
        if (mFormat == ImageFormat.NV21){
            OpenGLHelper.attachShader(mProgram, GLES30.GL_VERTEX_SHADER, VERTEX);
            OpenGLHelper.attachShader(mProgram, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_NV21);
            mYBuffer = ByteBuffer.allocate(mWidth * mHeight);
            mUVBuffer = ByteBuffer.allocate(mWidth * mHeight / 2);
        }else{
            throw new Exception("");
        }
        GLES30.glLinkProgram(mProgram);
        OpenGLHelper.outputProgramLog(mProgram);
        OpenGLHelper.checkError();


        GLES30.glGenBuffers(1, mBuffer, 0);
        OpenGLHelper.checkError();
        GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, mBuffer[0]);
        OpenGLHelper.checkError();
        GLES30.glBufferData(GLES30.GL_ARRAY_BUFFER, 4 * vertexs.length, FloatBuffer.wrap(vertexs), GLES30.GL_STATIC_DRAW);
        OpenGLHelper.checkError();
        GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, 0);

        GLES30.glGenVertexArrays(1, mVertexArray, 0);
        OpenGLHelper.checkError();
        GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, mBuffer[0]);
        OpenGLHelper.checkError();
        int vertexAttribLocation = GLES30.glGetAttribLocation(mProgram, "vertexPosition");
        OpenGLHelper.checkError();
        GLES30.glVertexAttribPointer(vertexAttribLocation, 3, GLES30.GL_FLOAT, false, 0, 0);
        OpenGLHelper.checkError();
        GLES30.glEnableVertexAttribArray(vertexAttribLocation);
        OpenGLHelper.checkError();
        int texturePositionLocation = GLES30.glGetAttribLocation(mProgram, "texturePosition");
        OpenGLHelper.checkError();
        GLES30.glVertexAttribPointer(texturePositionLocation, 2, GLES30.GL_FLOAT, false, 0, 3 * 4 * 4);
        OpenGLHelper.checkError();
        GLES30.glEnableVertexAttribArray(texturePositionLocation);
        OpenGLHelper.checkError();

        GLES30.glBindBuffer(GLES30.GL_ARRAY_BUFFER, 0);
        GLES30.glBindVertexArray(0);

        if (mFormat == ImageFormat.NV21){
            GLES30.glGenTextures(2, mTextures, 0);
            OpenGLHelper.checkError();
            setTextureTexParameter(mTextures[0], GLES30.GL_RED, GLES30.GL_RED, GLES30.GL_LINEAR, mWidth, mHeight);
            setTextureTexParameter(mTextures[1], GLES30.GL_RG, GLES30.GL_RG, GLES30.GL_LINEAR, mWidth / 2, mHeight / 2);
        }

        mInit = true;
    }

    public void setBuffer(byte[]yuv) throws Exception{
        try{
            mLock.lock();
            if (!mInit){
                throw new Exception("");
            }
            if (mFormat == ImageFormat.NV21){
                int length = mWidth * mHeight + mWidth * mHeight / 2;
                if (yuv.length < length){
                    throw new Exception("");
                }
                mYBuffer.clear();
                mYBuffer.put(yuv, 0, mWidth * mHeight);
                mYBuffer.flip();
                mUVBuffer.clear();
                mUVBuffer.put(yuv, mWidth * mHeight, mWidth * mHeight / 2);
                mUVBuffer.flip();
                mYUBBufferDirty = true;
            }else{
                throw new Exception("");
            }
        }finally {
            mLock.unlock();
        }
    }

    private void setTextureTexParameter(int texture, int innerFormat, int format, int filter, int width, int height) throws Exception{
        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, texture);
        OpenGLHelper.checkError();
        GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_MAG_FILTER, filter);
        OpenGLHelper.checkError();
        GLES30.glTexParameteri(GLES30.GL_TEXTURE_2D, GLES30.GL_TEXTURE_MIN_FILTER, filter);
        OpenGLHelper.checkError();
        GLES30.glTexImage2D(GLES30.GL_TEXTURE_2D, 0, innerFormat, width, height, 0, format, GLES30.GL_UNSIGNED_BYTE, null);
        OpenGLHelper.checkError();
    }

    public void release(){
        try{
            mLock.lock();
            if (0 != mProgram){
                GLES30.glDeleteProgram(mProgram);
                mProgram = 0;
            }
            if (0 != mBuffer[0]){
                GLES30.glDeleteBuffers(1, mBuffer, 0);
                mBuffer[0] = 0;
            }
        }finally {
            mLock.unlock();
        }
    }
}
