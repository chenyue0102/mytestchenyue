package com.xixi.observe.service.impl;

import com.xixi.observe.dao.UserEventDao;
import com.xixi.observe.dao.UserInfoDao;
import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.entity.UserEvent;
import com.xixi.observe.entity.UserInfo;
import com.xixi.observe.service.ErrorException;
import com.xixi.observe.service.UserEventService;
import com.xixi.observe.util.AccessTokenThreadLocal;
import com.xixi.observe.util.Result;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserEventServiceImp implements UserEventService {
    @Autowired
    UserEventDao userEventDao;
    @Autowired
    UserInfoDao userInfoDao;

    @Override
    public boolean insertUserEvent(UserEvent userEvent) {
        return userEventDao.insertUserEvent(userEvent);
    }

    @Override
    public List<UserEvent> findUserEvent(int userId, int eventId, long startTime, long endTime) throws ErrorException {
        AccessToken accessToken = AccessTokenThreadLocal.get();
        if (0 == userId || userId != accessToken.getUserId()){
            UserInfo userInfo = userInfoDao.getUserInfo(accessToken.getUserId());
            if (userInfo.getManager() != 0){
                throw new ErrorException(Result.CODE_PERMISSION_FAINED, Result.MSG_PERMISSION_FAILED);
            }
        }
        return userEventDao.findUserEvent(userId, eventId, startTime, endTime);
    }
}
