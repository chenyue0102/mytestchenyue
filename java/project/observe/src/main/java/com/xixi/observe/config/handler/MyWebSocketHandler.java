package com.xixi.observe.config.handler;

import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.handler.TextWebSocketHandler;

import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class MyWebSocketHandler extends TextWebSocketHandler {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    private static AtomicInteger onlineNum = new AtomicInteger();
    private static ConcurrentHashMap<String, WebSocketSession> sessionPools = new ConcurrentHashMap<>();

    @Override
    public void handleTextMessage(WebSocketSession session, TextMessage message) throws IOException {
        logger.warn("handleTextMessage");
        session.sendMessage(new TextMessage("recv:" + session.getAttributes().get("uid")
        + message.getPayload()));
    }

    @Override
    public void afterConnectionEstablished(WebSocketSession session)throws Exception{
        logger.warn("afterConnectionEstablished");
        String uid = session.getAttributes().get("uid").toString();
        sessionPools.put(uid, session);
        session.sendMessage(new TextMessage("afterConnectionEstablished"));
    }

    @Override
    public void afterConnectionClosed(WebSocketSession session, CloseStatus status)throws Exception{
        logger.warn("afterConnectionClosed");
        String uid = session.getAttributes().get("uid").toString();
        sessionPools.remove(uid);
    }
}
