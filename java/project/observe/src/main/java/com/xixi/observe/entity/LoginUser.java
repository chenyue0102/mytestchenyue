package com.xixi.observe.entity;

import lombok.Data;

@Data
public class LoginUser {
    private int id;

    private String name;

    private String loginName;

    private String password;

    private int state;
}
