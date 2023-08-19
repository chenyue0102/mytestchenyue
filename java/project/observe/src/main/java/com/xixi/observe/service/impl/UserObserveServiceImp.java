package com.xixi.observe.service.impl;

import com.xixi.observe.dao.UserObserveDao;
import com.xixi.observe.entity.UserObserveInfo;
import com.xixi.observe.service.UserObserveService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class UserObserveServiceImp implements UserObserveService {
    @Autowired
    UserObserveDao userObserveDao;
    @Override
    public List<UserObserveInfo> findUserObserveInfo(int userId, int observeUserId) {
        return userObserveDao.findUserObserveInfo(userId, observeUserId);
    }

    @Override
    public boolean insertUserObserveInfo(UserObserveInfo info) {
        return userObserveDao.insertUserObserveInfo(info);
    }
}
