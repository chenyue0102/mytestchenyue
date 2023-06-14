package com.xixi.observe.dao;

import com.xixi.observe.entity.LoginUser;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface LoginUserDao {
    LoginUser getLoginUser(String loginName);
}
