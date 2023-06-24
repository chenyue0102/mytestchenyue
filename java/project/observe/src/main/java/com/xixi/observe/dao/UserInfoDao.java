package com.xixi.observe.dao;

import com.xixi.observe.entity.LoginUser;
import com.xixi.observe.entity.UserInfo;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface UserInfoDao {
    LoginUser getLoginUser(String loginName);

    UserInfo getUserInfo(int userId);
}
