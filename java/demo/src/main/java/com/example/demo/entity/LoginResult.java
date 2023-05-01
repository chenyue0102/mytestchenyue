package com.example.demo.entity;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class LoginResult {
    @ApiModelProperty("访问token")
    public String accessToken;

    @ApiModelProperty("刷新token")
    public String refreshToken;
}
