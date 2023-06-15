package com.xixi.observe.entity;

import lombok.Data;

@Data
public class RefreshToken {
    private int userId;

    private long expirationTime;
}
