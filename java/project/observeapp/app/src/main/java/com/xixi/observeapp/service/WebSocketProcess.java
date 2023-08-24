package com.xixi.observeapp.service;


import android.content.Context;
import android.content.Intent;
import android.media.projection.MediaProjectionManager;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.xixi.observeapp.MyApplication;
import com.xixi.observeapp.activity.ScreenShotActivity;

import java.lang.reflect.Type;

import okhttp3.Response;
import okhttp3.WebSocket;
import okio.ByteString;

public class WebSocketProcess extends okhttp3.WebSocketListener {
    private static final String TAG = "WebSocketProcess";
    private Gson mGson = new Gson();

    private Context mContext;
    public WebSocketProcess(Context context){
        mContext = context;
    }
    @Override
    public void onOpen(WebSocket webSocket, Response response) {
        super.onOpen(webSocket, response);

    }

    @Override
    public void onMessage(WebSocket webSocket, String text) {
        super.onMessage(webSocket, text);
        WSProtocol.MsgBase msgBase = mGson.fromJson(text, WSProtocol.MsgBase.class);
        switch (msgBase.getMsgId()){
            case WSProtocol.MSG_SHOW_TIP_REQ:
                callFun(webSocket, text, this::onShowTip, new TypeToken<WSProtocol.MsgReqBase<WSProtocol.MsgShowTipReq>>(){}.getType());
                break;
            case WSProtocol.MSG_SCREEN_CAPTURE_REQ:
                callFun(webSocket, text, this::onScreenCapture, new TypeToken<WSProtocol.MsgReqBase<WSProtocol.MsgScreenCaptureReq>>(){}.getType());
                break;
            default:
                break;
        }
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

    private static interface CallFun<T>{
        void run(WebSocket webSocket, T t);
    }

    private <T> void callFun(WebSocket webSocket, String text, CallFun<T> imp, Type type){
        T t = mGson.fromJson(text, type);
        Log.w(TAG, "T:" + t.getClass().toString());
        imp.run(webSocket, t);
    }

    private <T> void sendMsg(WebSocket webSocket, WSProtocol.MsgReqBase req, T ackData, boolean success){
        WSProtocol.MsgAckBase<T> ack = new WSProtocol.MsgAckBase<T>();
        ack.setMsgId(req.getMsgId() + 1);
        ack.setSourceId(req.getDestUserId());
        ack.setDestUserId(req.getSourceId());
        ack.setSuccess(success);
        ack.setData(ackData);
        String json = mGson.toJson(ack);
        Log.w(TAG, json);
        webSocket.send(json);
    }

    private void onShowTip(WebSocket webSocket, WSProtocol.MsgReqBase<WSProtocol.MsgShowTipReq> req){
        Log.w(TAG, req.getData().getText());
        Handler handler = new Handler(Looper.getMainLooper()) ;
        handler.post(() -> Toast.makeText(MyApplication.getContext(), req.getData().getText(), Toast.LENGTH_LONG).show());

        WSProtocol.MsgShowTipAck ack = new WSProtocol.MsgShowTipAck();
        ack.setText(req.getData().getText());
        sendMsg(webSocket, req, ack, true);
    }

    private void onScreenCapture(WebSocket webSocket, WSProtocol.MsgReqBase<WSProtocol.MsgScreenCaptureReq> req){
        mScreenCaptureReq = req;

        Intent intent = new Intent(mContext, ScreenShotActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        mContext.startActivity(intent);
    }

    WSProtocol.MsgReqBase<WSProtocol.MsgScreenCaptureReq> mScreenCaptureReq;
    public void onScreenCaptureResult(WebSocket webSocket, int width, int height, String img){
        WSProtocol.MsgScreenCaptureAck ack = new WSProtocol.MsgScreenCaptureAck();
        ack.setImg(img);
        ack.setWidth(width);
        ack.setHeight(height);
        sendMsg(webSocket, mScreenCaptureReq, ack, null != img);
        mScreenCaptureReq = null;
        Log.w(TAG, "onScreenCaptureResult" + width);
    }
}
