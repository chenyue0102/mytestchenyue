package com.xixi.observe.service;

import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.ServiceRandomResult;
import com.xixi.observe.service.impl.UserServiceImpl;
import lombok.Data;

public interface UserService {
    class ErrorException extends Exception {
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

    ServiceRandomResult getServiceRandom();

    LoginResult login(LoginRequest loginRequest)throws ErrorException;
}
