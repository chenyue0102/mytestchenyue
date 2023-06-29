package com.xixi.observe.entity;

import lombok.Data;

@Data
public class RefreshToken {
    private int userId;

    //过期时间戳，单位秒
    private long expirationTime;
}
