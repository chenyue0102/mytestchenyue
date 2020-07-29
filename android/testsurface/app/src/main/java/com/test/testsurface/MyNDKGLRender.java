package com.test.testsurface;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyNDKGLRender implements GLSurfaceView.Renderer  {

    public MyNDKGLRender(){

    }
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        init();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        surfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        drawFrame();
    }

    private native void init();
    private native void surfaceChanged(int width, int height);
    private native void drawFrame();
}
