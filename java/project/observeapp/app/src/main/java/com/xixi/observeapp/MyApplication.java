package com.xixi.observeapp;

import android.app.Application;
import android.content.Context;

public class MyApplication extends Application {
    private static Context mContext;
    public static Context getContext(){
        return mContext;
    }

    public void onCreate(){
        super.onCreate();
        MyApplication.mContext = getApplicationContext();
    }
}
