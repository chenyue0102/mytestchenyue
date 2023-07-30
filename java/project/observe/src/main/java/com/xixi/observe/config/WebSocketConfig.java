package com.xixi.observe.config;

import com.xixi.observe.config.handler.MyWebSocketHandler;
import com.xixi.observe.interceptor.MyHandshakeInterceptor;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.socket.WebSocketHandler;
import org.springframework.web.socket.config.annotation.EnableWebSocket;
import org.springframework.web.socket.config.annotation.WebSocketConfigurer;
import org.springframework.web.socket.config.annotation.WebSocketHandlerRegistry;

import javax.annotation.Resource;

@Configuration
@EnableWebSocket
public class WebSocketConfig implements WebSocketConfigurer {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Resource
    private MyHandshakeInterceptor myHandshakeInterceptor;

    @Override
    public void registerWebSocketHandlers(WebSocketHandlerRegistry webSocketHandlerRegistry){
        webSocketHandlerRegistry
                //.addHandler(myHandler())
                .addHandler(myHandler(), "/ws")
                .setAllowedOrigins("*")
                .addInterceptors(myHandshakeInterceptor);
    }

    @Bean
    public WebSocketHandler myHandler(){
        return new MyWebSocketHandler();
    }
}
