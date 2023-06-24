package com.xixi.observe.entity;

import lombok.Data;

@Data
public class UserEventRequest {
    private int eventId;
    //时间戳，单位毫秒
    private long timestamp;
    private int data;
}
