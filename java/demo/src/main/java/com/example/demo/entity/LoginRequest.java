package com.example.demo.entity;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

import javax.validation.constraints.NotEmpty;

@Data
public class LoginRequest {
    @ApiModelProperty("登录名")
    @NotEmpty
    private String loginName;

    @ApiModelProperty("密码sha256")
    @NotEmpty
    private String passwordHash;
}
