package com.xixi.observeapp;

import android.app.Application;
import android.content.Context;

import com.xixi.observeapp.service.WebSocketService;

public class MyApplication extends Application {
    private static Context mContext;
    public static Context getContext(){
        return mContext;
    }

    private WebSocketService.MyBinder myBinder;

    public void onCreate(){
        super.onCreate();
        MyApplication.mContext = getApplicationContext();
    }

    public WebSocketService.MyBinder getMyBinder(){
        return myBinder;
    }

    public void setMyBinder(WebSocketService.MyBinder myBinder){
        this.myBinder = myBinder;
    }
}
