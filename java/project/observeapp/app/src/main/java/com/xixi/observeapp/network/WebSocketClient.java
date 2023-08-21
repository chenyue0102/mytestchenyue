package com.xixi.observeapp.network;

import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.WebSocket;
import okhttp3.WebSocketListener;
import okio.ByteString;

public class WebSocketClient {
    private static WebSocketClient instance;
    public static WebSocketClient getInstance(){
        if (null == instance){
            synchronized (WebSocketClient.class){
                if (null == instance){
                    instance = new WebSocketClient();
                }
            }
        }
        return instance;
    }

    private WebSocket mWebSocket;

    public void init(String serverAddress, String token){
        OkHttpClient client = new OkHttpClient.Builder()
                .pingInterval(10, TimeUnit.MINUTES)
                .build();
        Request request = new Request.Builder()
                .url(serverAddress)
                .addHeader("token", token)
                .build();
        mWebSocket = client.newWebSocket(request, new WebSocketListener() {
            @Override
            public void onOpen(WebSocket webSocket, Response response) {
                super.onOpen(webSocket, response);
            }

            @Override
            public void onMessage(WebSocket webSocket, String text) {
                super.onMessage(webSocket, text);
            }

            @Override
            public void onMessage(WebSocket webSocket, ByteString bytes) {
                super.onMessage(webSocket, bytes);
            }

            @Override
            public void onClosing(WebSocket webSocket, int code, String reason) {
                super.onClosing(webSocket, code, reason);
            }

            @Override
            public void onClosed(WebSocket webSocket, int code, String reason) {
                super.onClosed(webSocket, code, reason);
            }

            @Override
            public void onFailure(WebSocket webSocket, Throwable t, Response response) {
                super.onFailure(webSocket, t, response);
            }
        });

    }
}
