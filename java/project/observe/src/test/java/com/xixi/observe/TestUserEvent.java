package com.xixi.observe;

import com.xixi.observe.entity.UserEvent;
import com.xixi.observe.service.impl.UserEventServiceImp;
import com.xixi.observe.service.impl.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.sql.Timestamp;
import java.util.List;

@SpringBootTest
public class TestUserEvent {
    private static final Logger logger = LoggerFactory.getLogger(UserServiceImpl.class);
    @Autowired
    UserEventServiceImp userEventService;

    @Test
    void testInsertUserEvent(){
        UserEvent userEvent = new UserEvent();
        userEvent.setUserId(1);
        userEvent.setEventId(1);
        userEvent.setTimestamp(1687428713000L);
        userEvent.setData(0);
        boolean ret = userEventService.insertUserEvent(userEvent);
        logger.warn("ret:" + ret);
    }

    @Test
    void findUserEvent(){
        List<UserEvent> user1Event =  userEventService.findUserEvent(1, 0, 0, 0);
        List<UserEvent> event1 = userEventService.findUserEvent(0, 1, 0, 0);
        List<UserEvent> u1e1 = userEventService.findUserEvent(1, 1, 0, 0);
        List<UserEvent> t = userEventService.findUserEvent(0, 0, 0, 200);
        //List<UserEvent> t = userEventService.findUserEvent(0, 0, 100, 0);
        logger.warn("findUserEvent result");
    }
}
