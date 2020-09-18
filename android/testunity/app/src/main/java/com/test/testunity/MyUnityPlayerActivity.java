package com.test.testunity;

import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import com.unity3d.player.UnityMessagePlayerActivity;

public class MyUnityPlayerActivity extends UnityMessagePlayerActivity {

    public MyUnityPlayerActivity(){
        super();
        delaySendMsg();
    }

    public void delaySendMsg(){
        Log.i("MyUnityPlayerActivity", "delaySendMsg");
        new Handler().postDelayed(()->{
            String paramText = "{\"msgId\":100, \"action\":\"Put Bomb\"}";//参数字符串
            unitySendMessage(paramText);
        }, 5000);
    }

    @Override
    protected void onUnityMessage(String msgText) {
        Log.i("MyUnityPlayerActivity", "receive unitymsg:" + msgText);
    }

}
