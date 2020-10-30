package com.ksstory.spinewrap;

public class SpineItemJNI {
    public final static native long new_SpineItem();
    public final static native void delete_SpineItem(long swigCPtr);
    public final static native void setAtlasFile(long swigCPtr, String filePath);
    public final static native void setSkeletonFile(long swigCPtr, String filePath);
    public final static native boolean create(long swigCPtr, long textureLoaderSWigCPtr);
    public final static native void setAnimation(long swigCPtr, int trackIndex, String name, boolean loop);
    public final static native long getSkeleton(long swigCPtr);
    public final static native void updateSkeletonAnimation(long swigCPtr, float delta);
    public final static native void renderToCache(long swigCPtr, long swigCPtrRender);
}
