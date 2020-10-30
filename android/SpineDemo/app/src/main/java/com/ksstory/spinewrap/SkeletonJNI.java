package com.ksstory.spinewrap;

public class SkeletonJNI {
    public final static native void setPositon(long swigCPtr, float x, float y);
    public final static native void setScaleX(long swigCPtr, float scaleX);
    public final static native void setScaleY(long swigCPtr, float scaleY);
    public final static native void updateWorldTransform(long swigCPtr);
}
