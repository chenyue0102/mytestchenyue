package com.xixi.observe.config;

import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import com.xixi.observe.util.TokenUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.CloseStatus;
import org.springframework.web.socket.TextMessage;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.WebSocketSession;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;
import org.springframework.web.socket.handler.TextWebSocketHandler;
import org.springframework.web.socket.server.HandshakeInterceptor;

import javax.annotation.Resource;
import java.io.IOException;
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
            String token = serverHttpRequest.getServletRequest().getParameter("token");
            logger.warn("beforeHandshake:" + token);
            AccessToken accessToken = new AccessToken();
            if (TokenUtil.getInstance().checkAccessTokenAndConvert(token, accessToken)){
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

    static class MyWebSocketHandler extends TextWebSocketHandler {
        private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
        //key userid
        private static ConcurrentHashMap<Integer, WebSocketSession> sessionPools = new ConcurrentHashMap<>();

        @Override
        public void handleTextMessage(WebSocketSession session, TextMessage message) throws IOException {
            logger.warn("handleTextMessage");
            AccessToken accessToken = (AccessToken) session.getAttributes().get("token");
            session.sendMessage(new TextMessage("recv:" + accessToken.getUserId()
                    + message.getPayload()));
        }

        @Override
        public void afterConnectionEstablished(WebSocketSession session)throws Exception{
            logger.warn("afterConnectionEstablished");
            Object obj = session.getAttributes().get("token");
            if (null  == obj || !(obj instanceof AccessToken)){
                logger.warn("afterConnectionEstablished token failed");
                return;
            }
            AccessToken accessToken = (AccessToken)obj;
            sessionPools.put(accessToken.getUserId(), session);
            session.sendMessage(new TextMessage("afterConnectionEstablished"));
        }

        @Override
        public void afterConnectionClosed(WebSocketSession session, CloseStatus status)throws Exception{
            logger.warn("afterConnectionClosed");
            AccessToken accessToken = (AccessToken)session.getAttributes().get("token");
            sessionPools.remove(accessToken.getUserId());
        }
    }

    @Bean
    public WebSocketHandler myHandler(){
        return new MyWebSocketHandler();
    }
}
