package com.ksstory.spinewrap;

import android.util.Log;

/**
 * 只能够在主线程访问
 */
public class Skeleton extends BaseWrap{

    public Skeleton(long swigCPtr){
        super(swigCPtr, false);
    }

    public void setPosition(float x, float y){
        SkeletonJNI.setPositon(swigCPtr, x, y);
    }

    public void setScaleX(float scaleX){
        SkeletonJNI.setScaleX(swigCPtr, scaleX);
    }

    public void setScaleY(float scaleY){
        SkeletonJNI.setScaleY(swigCPtr, scaleY);
    }

    public void updateWorldTransform(){
        SkeletonJNI.updateWorldTransform(swigCPtr);
    }

    @Override
    protected void onDeleteJNI(long swigCPtr) {
        Log.e("Skeleton", "错误");
    }
}
