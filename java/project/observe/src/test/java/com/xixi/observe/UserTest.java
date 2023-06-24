package com.xixi.observe;

import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.UserInfo;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class UserTest {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Autowired
    UserInfoServiceImpl userService;

    @Test
    void testLogin(){
        LoginRequest loginRequest = new LoginRequest();
        loginRequest.setLoginName("zhangsan");
        try{
            LoginResult loginResult = userService.login(loginRequest, "");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    @Test
    void testGetUser(){
        UserInfo userInfo = userService.getUserInfo(1);
        logger.warn("userInfo:" + userInfo.toString());
    }
}
