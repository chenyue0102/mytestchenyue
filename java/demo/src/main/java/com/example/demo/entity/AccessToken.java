package com.example.demo.entity;

import lombok.Data;

@Data
public class AccessToken {
    private int userId;

    private long expirationTime;
}
