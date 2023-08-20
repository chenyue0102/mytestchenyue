package com.xixi.observeapp.bean;

import lombok.Data;
import org.hibernate.validator.constraints.NotEmpty;

@Data
public class LoginRequest {
    @NotEmpty
    private String loginName;

    //hash(password+serverRandom+clientRandom)
    @NotEmpty
    private String passwordHash;

    @NotEmpty
    private String serverRandom;

    @NotEmpty
    private String clientRandom;

    //验证码结果
    @NotEmpty
    private String verifyCode;

    //验证码 uuid
    @NotEmpty
    private String verifyCodeUUID;
}
