package com.xixi.observeapp.bean;

import lombok.Data;

@Data
public class LoginResult {
    private String accessToken;

    private String refreshToken;
}
