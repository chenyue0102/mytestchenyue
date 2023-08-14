package com.xixi.observe.config;

import com.xixi.observe.entity.LoginProperties;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class ConfigBeanConfiguration {
    @Bean
    public LoginProperties loginProperties(){
        return new LoginProperties();
    }
}
