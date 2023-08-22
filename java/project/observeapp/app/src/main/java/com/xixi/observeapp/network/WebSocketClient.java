package com.xixi.observeapp.network;

import android.util.Log;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.WebSocket;
import okhttp3.WebSocketListener;
import okio.ByteString;

public class WebSocketClient {
    private static final String TAG = "WebSocketClient";
    private static final int NORMAL_CLOSURE = 1000;

    private WebSocket mWebSocket;
    private Lock mLock = new ReentrantLock();
    private WebSocketListenerImp mWebSocketListenerImp;

    private WebSocketListener mListener;

    public WebSocketClient(){

    }

    public void setWebSocketListener(WebSocketListener listener){
        try{
            mLock.lock();
            mListener = listener;
        }finally {
            mLock.unlock();
        }
    }

    public void init(String serverAddress, String token){
        try{
            mLock.lock();
            innerDestroy();
            innerInit(serverAddress, token);
        }finally {
            mLock.unlock();
        }
    }

    public void destroy(){
        try{
            mLock.lock();
            innerDestroy();
        }finally {
            mLock.unlock();
        }
    }

    public void sendMsg(String msg){
        try{
            mLock.lock();
            if (null != mWebSocket){
                mWebSocket.send(msg);
            }
        }finally {
            mLock.unlock();
        }
    }

    public void sendData(ByteString data){
        try{
            mLock.lock();
            if (null != mWebSocket){
                mWebSocket.send(data);
            }
        }finally {
            mLock.unlock();
        }
    }

    private static class WebSocketListenerImp extends WebSocketListener{
        private WebSocketListener mCallback;
        private Lock mLock = new ReentrantLock();
        public WebSocketListenerImp(){

        }

        public void setCallback(WebSocketListener callback){
            try{
                mLock.lock();
                mCallback = callback;
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onOpen(WebSocket webSocket, Response response) {
            super.onOpen(webSocket, response);
            try{
                mLock.lock();
                if (null != mCallback) {
                    mCallback.onOpen(webSocket, response);
                }
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onMessage(WebSocket webSocket, String text) {
            super.onMessage(webSocket, text);
            try{
                mLock.lock();
                if (null != mCallback) {
                    mCallback.onMessage(webSocket, text);
                }
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onMessage(WebSocket webSocket, ByteString bytes) {
            super.onMessage(webSocket, bytes);
            try{
                mLock.lock();
                if (null != mCallback) {
                    mCallback.onMessage(webSocket, bytes);
                }
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onClosing(WebSocket webSocket, int code, String reason) {
            super.onClosing(webSocket, code, reason);
            try{
                mLock.lock();
                if (null != mCallback) {
                    mCallback.onClosing(webSocket, code, reason);
                }
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onClosed(WebSocket webSocket, int code, String reason) {
            super.onClosed(webSocket, code, reason);
            try{
                mLock.lock();
                if (null != mCallback){
                    mCallback.onClosed(webSocket, code, reason);
                }
            }finally {
                mLock.unlock();
            }
        }

        @Override
        public void onFailure(WebSocket webSocket, Throwable t, Response response) {
            super.onFailure(webSocket, t, response);
            try{
                mLock.lock();
                if (null != mCallback){
                    mCallback.onFailure(webSocket, t, response);
                }
            }finally {
                mLock.unlock();
            }
        }
    }

    private void innerInit(String serverAddress, String token){
        OkHttpClient client = new OkHttpClient.Builder()
                .pingInterval(10, TimeUnit.MINUTES)
                .build();
        Request request = new Request.Builder()
                .url(serverAddress)
                .addHeader("token", token)
                .build();
        mWebSocketListenerImp = new WebSocketListenerImp();
        mWebSocketListenerImp.setCallback(mListener);
        mWebSocket = client.newWebSocket(request, mWebSocketListenerImp);
    }

    private void innerDestroy(){
        if (null != mWebSocket){
            mWebSocketListenerImp.setCallback(null);
            mWebSocket.close(NORMAL_CLOSURE, "bye bye");
            mWebSocket = null;
            mWebSocketListenerImp = null;
        }
    }
}
