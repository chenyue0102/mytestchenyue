package com.test.testsensor;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

public class MyDrawView extends View {
    public float mX = 0.0f, mY = 0.0f;
    public float mWidth = 0, mHeight = 0;
    private float mRadius = 10.0f;
    private Paint mPaint = new Paint();

    public MyDrawView(Context context){
        super(context);
        init();
    }

    public MyDrawView(Context context, AttributeSet attrs){
        super(context, attrs);
        init();
    }

    @Override
    public void onWindowFocusChanged(boolean hasWindowFocus){
        super.onWindowFocusChanged(hasWindowFocus);
        mWidth = getWidth();
        mHeight = getHeight();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawCircle(mX, mY, mRadius, mPaint);
    }



    private void init(){
        mPaint.setColor(Color.RED);
        mPaint.setStrokeWidth(2);
    }
}
