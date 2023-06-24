package com.xixi.observe.entity;

import lombok.Data;

import java.sql.Timestamp;

@Data
public class UserEvent {
    private int userId;
    private int eventId;
    //毫秒时间戳
    private long timestamp;
    private int data;
}
