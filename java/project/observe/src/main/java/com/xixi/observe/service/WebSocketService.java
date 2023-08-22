package com.xixi.observe.service;

import com.google.gson.Gson;
import com.xixi.observe.entity.AccessToken;
import lombok.Data;
import org.springframework.stereotype.Service;
import org.springframework.web.socket.BinaryMessage;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;

import java.util.HashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

@Service
public class WebSocketService {
    private Gson mGson = new Gson();
    private Lock mLock = new ReentrantLock();
    private HashMap<Integer, WebSocketSession> mSessionMap = new HashMap<>();

    public void onClientConnected(WebSocketSession session){
        try{
            mLock.lock();
            innerOnClientConnected(session);
        }finally {
            mLock.unlock();
        }
    }

    public void onClientDisconnected(WebSocketSession session){
        try{
            mLock.lock();
            innerOnClientDisconnected(session);
        }finally {
            mLock.unlock();
        }
    }
    @Data
    public static class MsgBase{
        private int msgId;
        private int sourceId;
        private int destUserId;
    }

    @Data
    public static class MsgReqBase<T> extends MsgBase{
        private T data;
    }
    @Data
    public static class MsgAckBase<T> extends MsgBase{
        private boolean success;
        private T data;
    }

    public static final int MSG_SHOW_TIP_REQ = 1;
    @Data
    public static class MsgShowTipReq{
        private String text;
    }
    public static final int MSG_SHOW_TIP_ACK = 1;
    @Data
    public static class MsgShowTipAck extends MsgBase{
        private boolean success;
        private String text;
    }

    public void handleTextMessage(WebSocketSession session, TextMessage message){
        try{
            mLock.lock();
            innerHandleTextMessage(session, message);
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            mLock.unlock();
        }
    }

    public void handleBinaryMessage(WebSocketSession session, BinaryMessage message){

    }

    private void innerOnClientConnected(WebSocketSession session){
        AccessToken accessToken = (AccessToken)session.getAttributes().get("token");
        int userId = accessToken.getUserId();
        if (mSessionMap.get(userId) != null){
            WebSocketSession oldSession = mSessionMap.remove(userId);
            try{
                oldSession.close();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        mSessionMap.put(userId, session);
    }

    private void innerOnClientDisconnected(WebSocketSession session){
        AccessToken accessToken = (AccessToken)session.getAttributes().get("token");
        mSessionMap.remove(accessToken.getUserId());
    }

    private void innerHandleTextMessage(WebSocketSession session, TextMessage message)throws Exception{
        String text = message.getPayload();
        MsgBase msgBase = mGson.fromJson(text, MsgBase.class);
        WebSocketSession destSession = mSessionMap.get(msgBase.destUserId);
        if (null == destSession && (msgBase.getMsgId() % 2) == 1){
            MsgAckBase msgAckBase = new MsgAckBase();
            msgAckBase.setMsgId(msgBase.getMsgId() + 1);
            msgAckBase.setDestUserId(msgBase.getSourceId());
            msgAckBase.setSourceId(-1);
            msgAckBase.setSuccess(false);
            String json = mGson.toJson(msgAckBase);
            session.sendMessage(new TextMessage(json));
        }else{
            destSession.sendMessage(message);
        }
    }
}
