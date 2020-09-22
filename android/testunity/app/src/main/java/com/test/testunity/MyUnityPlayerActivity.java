package com.test.testunity;

import android.content.Intent;
import android.os.Handler;
import android.util.Log;

import com.google.gson.Gson;
import com.unity3d.player.UnityMessagePlayerActivity;

public class MyUnityPlayerActivity extends UnityMessagePlayerActivity {
    private Gson mGson = new Gson();

    public static class UnityMessageHeader{
        int msgId;
    }

    public MyUnityPlayerActivity(){
        super();
        delaySendMsg();
    }

    public void delaySendMsg(){
        Log.i("MyUnityPlayerActivity", "delaySendMsg");
        new Handler().postDelayed(()->{
            String sdcard = StorageHelper.getSDCardPath();
            //String paramText = "{\"msgId\":100, \"action\":\"Put Bomb\"}";//参数字符串
            String paramText = "{\"msgId\":2, \"filePath\":\"/storage/emulated/0/AssetScene.unity3d\",\"scene\":\"AssetScene\"}";//参数字符串
            //unitySendMessage(paramText);
            Intent intent = new Intent(this, PopActivity.class);
            startActivity(intent);
        }, 5000);
    }

    @Override
    protected void onUnityMessage(String msgText) {
        Log.i("MyUnityPlayerActivity", "receive unitymsg:" + msgText);
        UnityMessageHeader unityMessageHeader = mGson.fromJson(msgText, UnityMessageHeader.class);
        if (unityMessageHeader.msgId == 2){
            finish();
        }
    }

    @Override
    protected String updateUnityCommandLineArguments(String cmdLine){
        String assetCmd = "-asset file:///storage/emulated/0/data.unity3d";
        if (null == cmdLine){
            cmdLine = assetCmd;
        }else{
            cmdLine += " "+ assetCmd;
        }
        return cmdLine;
    }

}
