package com.test.testcamera;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class MySurfaceView extends GLSurfaceView {
    private MyYUVRender myYUVRender;

    public MySurfaceView(Context context){
        this(context, null);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    private void initView(){
        setEGLContextClientVersion(3);
        myYUVRender = new MyYUVRender();
        setRenderer(myYUVRender);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public void setInfo(int width, int height, int format){
        myYUVRender.setInfo(width, height, format);
    }

    public void setBuffer(byte []yuv) throws Exception{
        myYUVRender.setBuffer(yuv);
    }
}
