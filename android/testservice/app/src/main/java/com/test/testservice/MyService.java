package com.test.testservice;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;


public class MyService extends Service {
    private static final String TAG = "mytest";
    public MyService() {
    }

    MyBinder myBinder = new MyBinder();
    public class MyBinder extends Binder {
        public MyService getService() {
            return MyService.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.i(TAG, "MyService onBind " + toString());
        return myBinder;
    }

    @Override
    public boolean onUnbind(Intent intent){
        Log.i(TAG, "MyService onUnbind " + toString());
        return super.onUnbind(intent);
    }

    @Override
    public void onRebind(Intent intent) {
        Log.i(TAG, "MyService onRebind " + toString());
        super.onRebind(intent);
    }

    @Override
    public void onCreate(){
        super.onCreate();
        Log.i(TAG, "MyService onCreate " + toString());
    }

    @Override
    public void onDestroy(){
        Log.i(TAG, "MyService onDestroy " + toString());
        super.onDestroy();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId){
        int ret = super.onStartCommand(intent, flags, startId);
        Log.i(TAG, "MyService onStartCommand " + toString());
        return ret;
    }
}
