package com.xixi.observe.config;

import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.jasypt.util.text.BasicTextEncryptor;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.context.properties.EnableConfigurationProperties;
import org.springframework.boot.jdbc.DataSourceBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.env.Environment;

import javax.sql.DataSource;

@Configuration
@EnableConfigurationProperties(JdbcProperties.class)
public class JdbcConfiguration {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Autowired
    private JdbcProperties jdbcProperties;
    //@Autowired
    //private BasicTextEncryptor basicTextEncryptor;
    @Autowired
    private Environment env;

    @Bean
    public DataSource dataSource(){
        //basicTextEncryptor.setPassword();
        logger.warn("~~~~~~~~~~~~~~~~~~~~~dataSource~~~~~~~~~~~~~~~~~~~");
        String pwd = env.getProperty("jasypt.encryptor.password");
        logger.warn("password:" + pwd);
        BasicTextEncryptor basicTextEncryptor = new BasicTextEncryptor();
        basicTextEncryptor.setPassword(pwd);
        logger.warn("driverClassName:" + jdbcProperties.getDriverClassName() + " url:" + jdbcProperties.getUrl());

        DataSourceBuilder dataSourceBuilder = DataSourceBuilder.create();
        dataSourceBuilder.driverClassName(jdbcProperties.getDriverClassName());
        dataSourceBuilder.url(jdbcProperties.getUrl());

        String username = basicTextEncryptor.decrypt(jdbcProperties.getUsername());
        String password = basicTextEncryptor.decrypt(jdbcProperties.getPassword());

        logger.warn("username:" + username + " password:" + password);

        dataSourceBuilder.username(username);
        dataSourceBuilder.password(password);

        return dataSourceBuilder.build();
    }
}
