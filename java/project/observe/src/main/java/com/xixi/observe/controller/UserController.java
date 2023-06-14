package com.xixi.observe.controller;

import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.ServiceRandomResult;
import com.xixi.observe.service.UserService;
import com.xixi.observe.service.impl.UserServiceImpl;
import com.xixi.observe.util.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class UserController {
    @Autowired
    UserServiceImpl userService;

    @GetMapping("/test")
    public String test(){
        return "test";
    }

    //请求随机数
    @GetMapping("/random")
    public Result<ServiceRandomResult> getRandom(){
        Result<ServiceRandomResult> result = new Result<>(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        result.setData(userService.getServiceRandom());
        return result;
    }

    @GetMapping("/login")
    public Result<LoginResult> login(LoginRequest loginRequest){
        Result<LoginResult> result = new Result<>(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        try{
            LoginResult loginResult = userService.login(loginRequest);
            result.setData(loginResult);
        }catch (UserService.ErrorException e){
            result.setCode(e.getCode());
            result.setMsg(e.getMsg());
        }
        return result;
    }
}
