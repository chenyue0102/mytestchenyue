package com.xixi.observe.entity;

import lombok.Data;

import java.sql.Timestamp;

@Data
public class UserInfo {
    private int UserId;
    private String name;
    private String loginName;
    private String password;
    private int state;
    private int manager;
    private Timestamp createTime;
    private Timestamp modifyTime;
}
