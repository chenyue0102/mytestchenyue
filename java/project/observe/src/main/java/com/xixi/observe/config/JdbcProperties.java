package com.xixi.observe.config;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;

@ConfigurationProperties(prefix = "spring.datasource")
@Data
public class JdbcProperties {
    private String driverClassName;
    private String url;
    private String username;
    private String password;

}
