package com.xixi.observe.entity;

import lombok.Data;

@Data
public class LoginCode {
    public static enum LoginCodeEnum {
        /**
         * 算数
         */
        ARITHMETIC,
        /**
         * 中文
         */
        CHINESE,
        /**
         * 中文闪图
         */
        CHINESE_GIF,
        /**
         * 闪图
         */
        GIF,
        SPEC
    }
    private LoginCodeEnum codeType;
    //过期时间，单位分钟
    private Long expiration = 2L;
    private int length = 2;
    private int width = 100;
    private int height = 36;
    private String fontName;
    private int fontSize = 25;
    private String codeKey;
}
