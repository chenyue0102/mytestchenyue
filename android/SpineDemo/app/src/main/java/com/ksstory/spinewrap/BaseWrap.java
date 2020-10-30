package com.ksstory.spinewrap;

/**
 * 提供基本的释放操作，可以用delete，释放cpp中内容
 */
public abstract class BaseWrap {

    public synchronized void delete() {
        if (swigCPtr != 0) {
            if (swigCMemOwn) {
                swigCMemOwn = false;
                onDeleteJNI(swigCPtr);
            }
            swigCPtr = 0;
        }
    }

    //以下内部使用
    protected abstract void onDeleteJNI(long swigCPtr);

    protected void finalize() {
        delete();
    }

    private BaseWrap(){

    }

    protected BaseWrap(long cPtr, boolean cMemoryOwn) {
        swigCMemOwn = cMemoryOwn;
        swigCPtr = cPtr;
    }

    protected long getId(){
        return swigCPtr;
    }

    protected transient long swigCPtr;
    protected transient boolean swigCMemOwn;
}
