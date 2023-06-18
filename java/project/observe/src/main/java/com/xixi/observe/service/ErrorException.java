package com.xixi.observe.service;

public class ErrorException extends Exception {
    public ErrorException(int code, String msg){
        this.code = code;
        this.msg = msg;
    }
    public int getCode(){
        return code;
    }
    public String getMsg(){
        return msg;
    }
    private int code;
    private String msg;
}
