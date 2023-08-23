package com.xixi.observeapp.service;


import android.app.Notification;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Intent;
import android.graphics.BitmapFactory;
import android.os.Binder;
import android.os.IBinder;

import androidx.annotation.Nullable;

import com.xixi.observeapp.R;
import com.xixi.observeapp.activity.MainActivity;
import com.xixi.observeapp.network.WebSocketClient;

import okhttp3.WebSocket;
import okhttp3.WebSocketListener;

public class WebSocketService extends Service {
    private static final String TAG = "WebSocketService";
    private WebSocketClient mClient = new WebSocketClient();
    private WebSocketProcess mWebSocketProcess;

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

        public void setScreenCaptureResult(int width, int height, String img){
            WebSocket webSocket = mClient.getWebSocket();
            mWebSocketProcess.onScreenCaptureResult(webSocket, width, height, img);
        }
    }

    private MyBinder myBinder = new MyBinder();

    public WebSocketService(){
        mWebSocketProcess = new WebSocketProcess(this);
        mClient.setWebSocketListener(mWebSocketProcess);
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return myBinder;
    }


    @Override
    public int onStartCommand(Intent intent, int flags, int startId){
        Notification.Builder builder = new Notification.Builder(this.getApplicationContext());

        Intent intentMain = new Intent(this, MainActivity.class);

        builder.setContentIntent(PendingIntent.getActivity(this, 0, intentMain, 0))
                .setLargeIcon(BitmapFactory.decodeResource(this.getResources(), R.mipmap.ic_launcher))
                .setContentTitle("title")
                .setSmallIcon(R.mipmap.ic_launcher)
                .setContentText("text")
                .setWhen(System.currentTimeMillis());
        Notification notification = builder.build();
        notification.defaults = Notification.DEFAULT_SOUND;
        startForeground(100, notification);
        return super.onStartCommand(intent, flags, startId);
    }

    @Override
    public void onDestroy(){
        stopForeground(true);
        super.onDestroy();
    }
}
