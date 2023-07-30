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
        loginRequest.setClientRandom("abcd");
        loginRequest.setServerRandom("eyJyYW5kb21Ub2tlbiI6IjFkMGYxNWYzLTYzYTktNGQ1My04ODk2LTFjMmY0NjhiMDJiMSIsImV4cGlyYXRpb25UaW1lIjoxNjkwOTAzNTExfQ==.0te9jm+qrWMftbNJd79OKhhj6Pr64AJv42toP0Cn/eU=");
        loginRequest.setPasswordHash("2e348c718da17da7eaab9030326295c3fe0e0580cf9780274b481489dd66a069");
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
