package com.xixi.observeapp.service;


import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;

import androidx.annotation.Nullable;

import com.xixi.observeapp.network.WebSocketClient;

import okhttp3.WebSocketListener;

public class WebSocketService extends Service {
    private static final String TAG = "WebSocketService";
    private WebSocketClient mClient = new WebSocketClient();

    public class MyBinder extends Binder{
        public void setWebSocketListener(WebSocketListener listener){
            WebSocketService.this.mClient.setWebSocketListener(listener);
        }

        public void connect(String serverAddress, String token){
            WebSocketService.this.mClient.init(serverAddress, token);
        }

        public void disconnect(){
            WebSocketService.this.mClient.destroy();
        }

        public void sendMsg(String msg){

        }
    }

    private MyBinder myBinder = new MyBinder();

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return myBinder;
    }
}
