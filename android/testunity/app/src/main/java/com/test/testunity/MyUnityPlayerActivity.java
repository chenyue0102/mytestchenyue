package com.test.testunity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import com.unity3d.player.UnityPlayerActivity;

public class MyUnityPlayerActivity extends UnityPlayerActivity {

    private static MyUnityPlayerActivity instance = null;
    public static MyUnityPlayerActivity getInstance(){
        return instance;
    }

    public MyUnityPlayerActivity(){
        super();
        delaySendMsg();
    }

    public void delaySendMsg(){
        new Handler().postDelayed(()->{
            String gameObjectName = "Player";//unity 对象名称
            String methodName = "OnAppMessage";//对象方法
            String paramText = "Put Bomb";//参数字符串
            mUnityPlayer.UnitySendMessage(gameObjectName, methodName, paramText);
        }, 5000);
    }

    public void unityCallback(String text){
        Log.i("MyUnityPlayerActivity", "unityCallback:" + text);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        MyUnityPlayerActivity.instance = this;
    }

    @Override
    protected void onDestroy(){
        MyUnityPlayerActivity.instance = null;
        super.onDestroy();
    }
}
