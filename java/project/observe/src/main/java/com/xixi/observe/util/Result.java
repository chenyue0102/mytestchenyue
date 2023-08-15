package com.xixi.observe.util;


import java.io.Serializable;

public class Result<T> implements Serializable {
    public static final int CODE_SUCCESS = 0;
    public static final String MSG_SUCCEEDED = "succeeded";
    public static final int CODE_FAILED = -1;
    public static final String MSG_FAILED = "failed";
    public static final int CODE_TOKEN_FAILED = -2;
    public static final String MSG_TOKEN_FAILED = "token failed";

    public static final int CODE_PERMISSION_FAINED = -3;

    public static final String MSG_PERMISSION_FAILED = "permission failed";

    public static final int CODE_VERIFY_CODE_FAILED = -4;
    public static final String MSG_VERIFY_CODE_FAILED = "verify code failed";

    public static final int CODE_VERIFY_CODE_EXPIRED = -5;
    public static final String MSG_VERIFY_CODE_EXPIRED = "verify code expired";

    public static final int CODE_METHOD_FAILED = -6;
    public static final String MSG_METHOD_FAILED = "method failed";

    private int code;

    private String msg;

    private T data;

    public Result(){

    }

    public Result(int code, String msg){
        this.code = code;
        this.msg = msg;
    }

    public int getCode(){
        return code;
    }

    public void setCode(int code){
        this.code = code;
    }

    public String getMsg(){
        return msg;
    }

    public void setMsg(String msg){
        this.msg = msg;
    }

    public T getData(){
        return data;
    }

    public void setData(T data){
        this.data = data;
    }

    @Override
    public String toString(){
        return "result{"+
                "code:"+code+
                "smg:"+msg+
                "data:"+data+
                "}";
    }
}
