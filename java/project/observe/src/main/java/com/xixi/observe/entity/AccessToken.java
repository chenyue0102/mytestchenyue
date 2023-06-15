package com.xixi.observe.entity;

import lombok.Data;

@Data
public class AccessToken {
    private int userId;

    private long expirationTime;
}
