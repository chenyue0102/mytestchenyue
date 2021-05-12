package com.test.myapplication;

import android.view.MotionEvent;
import android.view.View;

public class MouseMoveClickListener implements View.OnTouchListener{
    public interface IMouseMoveCallback{
        void onMouseMove(int offsetx, int offsety);
        void onMouseMoveStop();
        void onMouseClick();
    }

    private IMouseMoveCallback mCallback;
    private boolean mMoving = false;
    private int mLastX = 0;
    private int mLastY = 0;
    private long mDownTime = -1;
    private static final long MIN_CLICK_TIME = 100;//MS

    public MouseMoveClickListener(IMouseMoveCallback callback){
        mCallback = callback;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (null != mCallback){
            switch (event.getAction()){
                case MotionEvent.ACTION_MOVE:
                    int actionIndex = event.getActionIndex();
                    float x = event.getX(actionIndex);
                    float y = event.getY(actionIndex);
                    int dx = Math.round(x);
                    int dy = Math.round(y);
                    if (mMoving){
                        int diffx = dx - mLastX;
                        int diffy = dy - mLastY;
                        mCallback.onMouseMove(diffx, diffy);
                    }else{
                        mMoving = true;
                    }
                    mLastX = dx;
                    mLastY = dy;
                    break;
                case MotionEvent.ACTION_DOWN:
                    mDownTime = event.getEventTime();
                    break;
                case MotionEvent.ACTION_UP://最后一个手指抬起
                    mMoving = false;
                    mLastX = mLastY = 0;
                    mCallback.onMouseMoveStop();
                    if (-1 != mDownTime){
                        long diff = event.getEventTime() - mDownTime;
                        if (diff <= MIN_CLICK_TIME){
                            mCallback.onMouseClick();
                        }
                        mDownTime = -1;
                    }
                    break;
                default:
                    break;
            }
        }
        return true;
    }
}
