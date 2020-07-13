package com.test.testsurface;


import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.text.TextPaint;
import android.util.AttributeSet;
import android.util.TypedValue;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import androidx.annotation.RequiresApi;

import java.util.concurrent.atomic.AtomicBoolean;

public class MySurfaceView extends GLSurfaceView implements SurfaceHolder.Callback{
    private SurfaceHolder surfaceHolder;
    private AtomicBoolean mExit = new AtomicBoolean(false);

    public MySurfaceView(Context context){
        this(context, null);
    }

    public MySurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    private void initView(){
        surfaceHolder = getHolder();
        surfaceHolder.addCallback(this);
    }

    private void doDraw(){
        Canvas canvas = surfaceHolder.lockCanvas();
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);
        String str = "hello, world" + (System.currentTimeMillis() / 100);
        TextPaint textPaint = new TextPaint();
        textPaint.setTextAlign(Paint.Align.LEFT);
        textPaint.setColor(Color.GREEN);
        //float textSize =  TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, getResources().getDimension(R.dimen.text_size), getResources().getDisplayMetrics());
        float textSize =  TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 20, getResources().getDisplayMetrics());
        textPaint.setTextSize(textSize);
        canvas.drawText(str, 100.0f, 100.0f, textPaint);

        surfaceHolder.unlockCanvasAndPost(canvas);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    while (!mExit.get()){
                        doDraw();
                        Thread.sleep(100);
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
