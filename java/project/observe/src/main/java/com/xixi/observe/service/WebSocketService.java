package com.xixi.observe.service;

import com.google.gson.Gson;
import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.entity.WSProtocol;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;
import org.springframework.web.socket.BinaryMessage;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;

import java.util.HashMap;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

@Service
public class WebSocketService {
    private static final Logger logger = LoggerFactory.getLogger(WebSocketService.class);
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
        logger.warn("websocket:" + userId + " connected");
    }

    private void innerOnClientDisconnected(WebSocketSession session){
        AccessToken accessToken = (AccessToken)session.getAttributes().get("token");
        mSessionMap.remove(accessToken.getUserId());
        logger.warn("websocket:" + accessToken.getUserId() + " disconnected");
    }

    private void innerHandleTextMessage(WebSocketSession session, TextMessage message)throws Exception{
        String text = message.getPayload();
        if (WSProtocol.PING.equals(text)){
            session.sendMessage(new TextMessage(WSProtocol.PONG));
            return;
        }

        WSProtocol.MsgBase msgBase = mGson.fromJson(text, WSProtocol.MsgBase.class);
        WebSocketSession destSession = mSessionMap.get(msgBase.getDestUserId());
        if (null == destSession){
            if ((msgBase.getMsgId() % 2) == 1){
                WSProtocol.MsgAckBase msgAckBase = new WSProtocol.MsgAckBase();
                msgAckBase.setMsgId(msgBase.getMsgId() + 1);
                msgAckBase.setDestUserId(msgBase.getSourceId());
                msgAckBase.setSourceId(-1);
                msgAckBase.setSuccess(false);
                String json = mGson.toJson(msgAckBase);
                session.sendMessage(new TextMessage(json));
            }
        }else{
            destSession.sendMessage(message);
        }
    }
}
