package com.test.myapplication;

import android.view.MotionEvent;
import android.view.View;

public class MouseMoveListener implements View.OnTouchListener{
    public interface IMouseMoveCallback{
        void onMouseMove(int offsetx, int offsety);
        void onMouseMoveStop();
    }


    private boolean mMoving = false;
    private int mLastX = 0;
    private int mLastY = 0;
    private IMouseMoveCallback mIMouseMoveCallback = null;

    public MouseMoveListener(IMouseMoveCallback callback){
        mIMouseMoveCallback = callback;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (null != mIMouseMoveCallback){
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
                        mIMouseMoveCallback.onMouseMove(diffx, diffy);
                    }else{
                        mMoving = true;
                    }
                    mLastX = dx;
                    mLastY = dy;
                    break;
                case MotionEvent.ACTION_UP://最后一个手指抬起
                    mMoving = false;
                    mLastX = mLastY = 0;
                    mIMouseMoveCallback.onMouseMoveStop();
                    break;
                default:
                    break;
            }
        }
        return true;
    }
}
