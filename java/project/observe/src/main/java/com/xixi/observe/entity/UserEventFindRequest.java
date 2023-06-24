package com.xixi.observe.entity;

import lombok.Data;

@Data
public class UserEventFindRequest {
    private int userId;
    private int eventId;
    //毫秒时间戳
    private long startTime;
    private long endTime;
}
