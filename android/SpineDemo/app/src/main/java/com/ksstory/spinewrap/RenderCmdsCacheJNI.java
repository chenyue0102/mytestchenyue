package com.ksstory.spinewrap;

public class RenderCmdsCacheJNI {
    public final static native long new_RenderCmdsCache();
    public final static native void delete_RenderCmdsCache(long swigCPtr);
    public final static native void initShaderProgram(long swigCPtr, String vTexture, String fTexture, String vColor, String fColor);
    public final static native void setViewSize(long swigCPtr, float width, float height);
    public final static native void clearCache(long swigCPtr);
    public final static native void render(long swigCPtr);
}
