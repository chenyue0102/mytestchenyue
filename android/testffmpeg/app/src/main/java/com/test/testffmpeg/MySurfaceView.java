package com.test.testffmpeg;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

public class MySurfaceView extends GLSurfaceView {

    public MySurfaceView(Context context){
        this(context, null);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    private void initView(){
        setEGLContextClientVersion(3);
        MyRenderer myRenderer = new MyRenderer();
        setRenderer(myRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }
}
