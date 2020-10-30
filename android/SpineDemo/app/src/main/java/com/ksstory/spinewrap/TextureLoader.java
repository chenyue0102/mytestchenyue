package com.ksstory.spinewrap;

public class TextureLoader extends BaseWrap{

    public TextureLoader(){
        super(TextureLoaderJNI.new_TextureLoader(), true);
    }

    @Override
    protected void onDeleteJNI(long swigCPtr) {
        TextureLoaderJNI.delete_TextureLoader(swigCPtr);
    }
}
