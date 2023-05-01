package com.example.demo.dao;

import com.example.demo.entity.LoginUser;
import org.apache.ibatis.annotations.Mapper;

@Mapper
public interface LoginUserDao {
    LoginUser getLoginUser(String loginName);
}
