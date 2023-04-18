package com.example.demo;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.servlet.config.annotation.CorsRegistration;
import org.springframework.web.servlet.config.annotation.CorsRegistry;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

import java.util.List;

@Configuration
public class WebConfig implements WebMvcConfigurer {
    @Autowired
    UserTokenInterceptor userTokenInterceptor;
    @Override
    public void addInterceptors(InterceptorRegistry registry){
        Logger logger = LoggerFactory.getLogger(WebConfig.class);
        logger.debug("~~~~~~~~~~~~~~~~~addInterceptors before");
        registry.addInterceptor(this.userTokenInterceptor)
                .addPathPatterns("/**")
                .excludePathPatterns("/login");
        logger.debug("~~~~~~~~~~~~~~~~addInterceptors after");
    }

    @Override
    public void addCorsMappings(CorsRegistry registry){
        Logger logger = LoggerFactory.getLogger(WebConfig.class);
        logger.debug("~~~~~~~~~~~~~~~~addCorsMappings");
        registry.addMapping("/**")
                .allowCredentials(true)
                .allowedOrigins("*")
                .allowedMethods("GET", "PUT", "DELETE", "POST", "OPTIONS")
                .maxAge(3600);
    }

    @Override
    public void addArgumentResolvers(List<HandlerMethodArgumentResolver> resolvers){
        Logger logger = LoggerFactory.getLogger(WebConfig.class);
        logger.debug("~~~~~~~~~~~~~~~~addArgumentResolvers");
    }
}
