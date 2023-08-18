package com.xixi.observe.entity;

import lombok.Data;

import java.sql.Timestamp;
@Data
public class UserObserveInfo {
    private int userId;
    private int observeUserId;
    private Timestamp createTime;

}
