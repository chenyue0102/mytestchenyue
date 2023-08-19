package com.xixi.observe.service;

import com.xixi.observe.entity.UserObserveInfo;

import java.util.List;

public interface UserObserveService {
    List<UserObserveInfo> findUserObserveInfo(int userId, int observeUserId);

    boolean insertUserObserveInfo(UserObserveInfo info);
}
