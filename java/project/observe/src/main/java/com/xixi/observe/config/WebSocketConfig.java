package com.xixi.observe.config;

import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.service.WebSocketService;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.TokenUtil;
import io.netty.buffer.ByteBuf;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.*;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;
import org.springframework.web.socket.handler.AbstractWebSocketHandler;
import org.springframework.web.socket.handler.TextWebSocketHandler;
import org.springframework.web.socket.server.HandshakeInterceptor;

import javax.annotation.Resource;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@Configuration
@EnableWebSocket
public class WebSocketConfig implements WebSocketConfigurer {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Resource
    private MyHandshakeInterceptor myHandshakeInterceptor;

    @Override
    public void registerWebSocketHandlers(WebSocketHandlerRegistry webSocketHandlerRegistry){
        webSocketHandlerRegistry
                .addHandler(myHandler(), "/ws")
                .setAllowedOrigins("*")
                .addInterceptors(myHandshakeInterceptor);
    }

    @Component
    static class MyHandshakeInterceptor implements HandshakeInterceptor {
        private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
        @Override
        public boolean beforeHandshake(ServerHttpRequest request, ServerHttpResponse response,
                                       WebSocketHandler webSocketHandler, Map<String, Object> attributes){
            ServletServerHttpRequest serverHttpRequest = (ServletServerHttpRequest) request;
            String token = serverHttpRequest.getServletRequest().getHeader("token");
            logger.warn("beforeHandshake:" + token);
            AccessToken accessToken = new AccessToken();
            if (Result.CODE_SUCCESS == TokenUtil.getInstance().checkAccessTokenAndConvert(token, accessToken)){
                logger.warn("beforeHandshake" + "success");
                attributes.put("token", accessToken);
                return true;
            }else{
                logger.warn("beforeHandshake" + "failed");
                return false;
            }
        }

        @Override
        public void afterHandshake(ServerHttpRequest request, ServerHttpResponse response,
                                   WebSocketHandler webSocketHandler, Exception exception){
            logger.warn("afterHandshake");
        }
    }

    static class MyWebSocketHandler extends AbstractWebSocketHandler {
        private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
        private WebSocketService webSocketService = new WebSocketService();

        @Override
        public void handleTextMessage(WebSocketSession session, TextMessage message) throws Exception {
            webSocketService.handleTextMessage(session, message);
        }

        @Override
        public void handleBinaryMessage(WebSocketSession session, BinaryMessage message) throws Exception {
            super.handleBinaryMessage(session, message);
            webSocketService.handleBinaryMessage(session, message);
        }

        @Override
        public void afterConnectionEstablished(WebSocketSession session)throws Exception{
            logger.warn("afterConnectionEstablished");
            Object obj = session.getAttributes().get("token");
            if (null  == obj || !(obj instanceof AccessToken)){
                logger.warn("afterConnectionEstablished token failed");
                return;
            }
            webSocketService.onClientConnected(session);
        }

        @Override
        public void afterConnectionClosed(WebSocketSession session, CloseStatus status)throws Exception{
            logger.warn("afterConnectionClosed");
            webSocketService.onClientDisconnected(session);
        }
    }

    @Bean
    public WebSocketHandler myHandler(){
        return new MyWebSocketHandler();
    }
}
