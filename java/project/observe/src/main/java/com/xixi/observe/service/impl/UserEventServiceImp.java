package com.xixi.observe.service.impl;

import com.xixi.observe.dao.UserEventDao;
import com.xixi.observe.entity.UserEvent;
import com.xixi.observe.service.UserEventService;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserEventServiceImp implements UserEventService {
    @Autowired
    UserEventDao userEventDao;

    @Override
    public boolean insertUserEvent(UserEvent userEvent) {
        return userEventDao.insertUserEvent(userEvent);
    }

    @Override
    public List<UserEvent> findUserEvent(int userId, int eventId, long startTime, long endTime) {
        return userEventDao.findUserEvent(userId, eventId, startTime, endTime);
    }
}
