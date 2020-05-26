package com.test.testsurface;


import android.content.Context;
import android.graphics.Canvas;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import java.util.concurrent.atomic.AtomicBoolean;

public class MySurfaceView extends SurfaceView implements SurfaceHolder.Callback{
    private SurfaceHolder surfaceHolder;
    private Canvas canvas;
    private AtomicBoolean mExit = new AtomicBoolean(false);

    public MySurfaceView(Context context){
        super(context);
        initView();
    }

    private void initView(){
        surfaceHolder = getHolder();
        surfaceHolder.addCallback(this);
    }

    private void doDraw(){
        Canvas canvas = surfaceHolder.lockCanvas();
        canvas.drawText("hello", );
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    while (!mExit.get()){
                        doDraw();
                        Thread.sleep(40);
                    }
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
