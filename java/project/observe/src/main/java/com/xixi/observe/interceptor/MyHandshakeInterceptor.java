package com.xixi.observe.interceptor;

import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.http.server.ServerHttpRequest;
import org.springframework.http.server.ServerHttpResponse;
import org.springframework.http.server.ServletServerHttpRequest;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.server.HandshakeInterceptor;

import java.util.Map;

@Component
public class MyHandshakeInterceptor implements HandshakeInterceptor {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Override
    public boolean beforeHandshake(ServerHttpRequest request, ServerHttpResponse response,
                                   WebSocketHandler webSocketHandler, Map<String, Object> attributes){
        ServletServerHttpRequest serverHttpRequest = (ServletServerHttpRequest) request;
        String userId = serverHttpRequest.getServletRequest().getParameter("userId");
        attributes.put("uid", userId);
        //return false;
        return true;
    }

    @Override
    public void afterHandshake(ServerHttpRequest request, ServerHttpResponse response,
                               WebSocketHandler webSocketHandler, Exception exception){
        logger.warn("afterHandshake");
    }
}
