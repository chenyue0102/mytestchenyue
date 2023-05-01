package com.example.demo.entity;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class LoginRequest {
    @ApiModelProperty("登录名")
    private String loginName;

    @ApiModelProperty("密码sha256")
    private String passwordHash;
}
