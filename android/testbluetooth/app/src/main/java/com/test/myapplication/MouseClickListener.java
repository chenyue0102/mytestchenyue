package com.test.myapplication;

import android.view.MotionEvent;
import android.view.View;

public class MouseClickListener implements View.OnTouchListener{
    public interface IMouseClickCallback{
        void onMouseDown();
        void onMouseUp();
        void onMouseDbClick();
    }

    private IMouseClickCallback mCallback;
    private long mEventTime = -1;
    private static final int MAX_DBCLICK_INTERVAL = 100;//ms

    public MouseClickListener(IMouseClickCallback callback){
        mCallback = callback;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (null != mCallback){
            switch (event.getAction()){
                case MotionEvent.ACTION_DOWN:
                    mCallback.onMouseDown();
                    break;
                case MotionEvent.ACTION_UP:
                    mCallback.onMouseUp();
                    long eventTime = event.getEventTime();
                    if (-1 == mEventTime){
                        mEventTime = eventTime;
                    }else{
                        if (eventTime - mEventTime < MAX_DBCLICK_INTERVAL){
                            mCallback.onMouseDbClick();
                            mEventTime = -1;
                        }else{
                            mEventTime = eventTime;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        return true;
    }
}
