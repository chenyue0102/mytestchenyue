package com.unity3d.player;

import android.util.Log;

public class UnityMessageCallback{

    public void onUnityMessage(String msgText){
        UnityMessagePlayerActivity instance = UnityMessagePlayerActivity.getInstance();
        if (null != instance){
            instance.onUnityMessage(msgText);;
        }else{
            Log.e("UnityMessageCallback", "UnityMessagePlayerActivity instance == null failed");
        }
    }
}