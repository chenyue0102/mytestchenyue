package com.example.demo.entity;

import io.swagger.annotations.ApiModelProperty;
import lombok.Data;

@Data
public class LoginUser {
    @ApiModelProperty("用户id")
    private int id;

    @ApiModelProperty("用户名")
    private String name;

    @ApiModelProperty("登录名")
    private String loginName;

    @ApiModelProperty("密码")
    private String password;

    @ApiModelProperty("密码hash")
    private String passwordHash;
}
