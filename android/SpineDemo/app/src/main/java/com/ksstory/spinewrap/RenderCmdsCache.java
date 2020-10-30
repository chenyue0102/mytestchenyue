package com.ksstory.spinewrap;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * 绘制类
 */
public class RenderCmdsCache extends BaseWrap{

    private boolean mDirty;
    public RenderCmdsCache(){
        super(RenderCmdsCacheJNI.new_RenderCmdsCache(), true);
    }

    public void setDirty(){
        mDirty = true;
    }

    //初始化shader，只在GLSurfaceView.Renderer.onSurfaceCreated中访问
    public void initShaderProgram(String vTexture, String fTexture, String vColor, String fColor){
        RenderCmdsCacheJNI.initShaderProgram(swigCPtr, vTexture, fTexture, vColor, fColor);
    }

    //在onSurfaceChanged中调用
    public void setViewSize(float width, float height){
        RenderCmdsCacheJNI.setViewSize(swigCPtr, width, height);
    }

    //在绘制所有SpineItem之前，需要调用clearCache，防止内存中，还有上次没有绘制的项
    public void clearCache(){
        RenderCmdsCacheJNI.clearCache(swigCPtr);
    }

    //绘制到界面上，只在OpenGLES工作线程访问
    public void render(){
        if (mDirty){
            mDirty = false;
            RenderCmdsCacheJNI.render(swigCPtr);
        }
    }

    @Override
    protected void onDeleteJNI(long swigCPtr) {
        RenderCmdsCacheJNI.delete_RenderCmdsCache(swigCPtr);
    }
}
