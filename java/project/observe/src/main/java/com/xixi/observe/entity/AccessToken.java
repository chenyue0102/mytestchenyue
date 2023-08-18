package com.xixi.observe.entity;

import lombok.Data;

@Data
public class AccessToken {
    private int userId;

    private int manager;

    //过期时间戳，单位秒
    private long expirationTime;
}
