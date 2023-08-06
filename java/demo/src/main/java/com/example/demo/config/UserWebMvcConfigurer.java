package com.example.demo.config;

import com.example.demo.config.handler.TokenToUserMethodArguentResolver;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

@Configuration
public class UserWebMvcConfigurer implements WebMvcConfigurer {
    @Autowired
    private TokenToUserMethodArguentResolver tokenToUserMethodArguentResolver;
    public void addArgumentResolvers(List<HandlerMethodArgumentResolver> argumentResolvers){
        argumentResolvers.add(tokenToUserMethodArguentResolver);
    }
}