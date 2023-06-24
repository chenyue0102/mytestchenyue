package com.xixi.observe.config;

import com.xixi.observe.config.handler.ClientIpResolver;
import com.xixi.observe.config.handler.TokenResolver;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

@Configuration
public class UserWebMvcConfigurer implements WebMvcConfigurer {
    @Autowired
    private TokenResolver tokenResolver;

    @Autowired
    private ClientIpResolver clientIpResolver;

    @Autowired
    private UserTokenInterceptor userTokenInterceptor;

    public void addArgumentResolvers(List<HandlerMethodArgumentResolver> argumentResolvers){
        argumentResolvers.add(tokenResolver);
        argumentResolvers.add(clientIpResolver);
    }

    public void addInterceptors(InterceptorRegistry registry){
        registry.addInterceptor(userTokenInterceptor)
                .addPathPatterns("/**")
                .excludePathPatterns("/login");
    }
}
