package com.xixi.observe.entity;

import lombok.Data;

@Data
public class LoginResult {
    private String accessToken;

    private String refreshToken;
}