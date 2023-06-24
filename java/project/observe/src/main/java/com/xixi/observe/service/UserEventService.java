package com.xixi.observe.service;

import com.xixi.observe.entity.UserEvent;

import java.util.List;

public interface UserEventService {
    boolean insertUserEvent(UserEvent userEvent);
    //参数不为0，则有效，否则忽略
    List<UserEvent> findUserEvent(int userId, int eventId, long startTime, long endTime) throws ErrorException;
}
