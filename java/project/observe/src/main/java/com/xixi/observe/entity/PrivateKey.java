package com.xixi.observe.entity;

import lombok.Data;

import java.sql.Timestamp;

@Data
public class PrivateKey {
    //RSA2048私钥，需要去除\n
    private String privateKey;
    //启用时间
    private Timestamp enableTime;
    //过期时间
    private Timestamp expiration;
}
