package com.xixi.observe;

import com.xixi.observe.service.impl.UserInfoServiceImpl;
import com.xixi.observe.service.impl.UserObserveServiceImp;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class TestUserObserve {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Autowired
    UserObserveServiceImp userObserveService;
    @Test
    public void TestInsert(){
        int u1 = 1,u2=2;

    }

}
