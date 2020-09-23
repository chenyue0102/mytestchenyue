package com.unity3d.player;

import android.os.Bundle;

public abstract class UnityMessagePlayerActivity extends UnityPlayerActivity{
    public static final String UNITY_RECEIVE_OBJECT_NAME = "MessageBriage";
    public static final String UNITY_RECEIVE_METHOD_NAME = "OnAppMessage";
    private static UnityMessagePlayerActivity instance = null;
    public static UnityMessagePlayerActivity getInstance(){
        return UnityMessagePlayerActivity.instance;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        instance = this;
    }

    @Override
    protected void onDestroy(){
        instance = null;
        super.onDestroy();
    }

    /**
     * 发送信息给unity中的消息接收对象
     * @param msgText json格式的消息
     */
    public void unitySendMessage(String msgText){
        mUnityPlayer.UnitySendMessage(UNITY_RECEIVE_OBJECT_NAME, UNITY_RECEIVE_METHOD_NAME, msgText);
    }

    /**
     * 处理unity消息对象发送的消息
     * @param msgText json格式的消息
     */
    protected abstract void onUnityMessage(String msgText);
}