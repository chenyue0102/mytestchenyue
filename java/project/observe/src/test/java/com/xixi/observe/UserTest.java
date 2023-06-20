package com.xixi.observe;

import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.service.impl.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class UserTest {
    @Autowired
    UserServiceImpl userService;

    @Test
    void testLogin(){
        LoginRequest loginRequest = new LoginRequest();
        loginRequest.setLoginName("zhangsan");
        try{
            LoginResult loginResult = userService.login(loginRequest);
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
