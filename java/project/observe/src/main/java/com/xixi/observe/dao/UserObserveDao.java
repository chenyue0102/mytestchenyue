package com.xixi.observe.dao;

import com.xixi.observe.entity.UserObserveInfo;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

@Mapper
public interface UserObserveDao {
    boolean insertUserObserveInfo(UserObserveInfo info);
    List<UserObserveInfo> findUserObserveInfo(@Param("userId")int userId, @Param("observeUserId") int observeUserId);
}
