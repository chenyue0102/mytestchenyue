package com.example.demo.controller;

import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
@Api(value = "v1", tags = "tag")
@RequestMapping("/test")
public class TestController {
    static public class UserInfo{
        public String name;
        public int id;
    }

    List<UserInfo> mUserInfos;
    TestController(){
        mUserInfos = new ArrayList<>();
        for (int i = 0;i < 2; i++){
            UserInfo userInfo = new UserInfo();
            userInfo.id = i+1;
            userInfo.name = "name" + String.valueOf(i+1);
            mUserInfos.add(userInfo);
        }
    }

    @RequestMapping(value = "/hello", method = RequestMethod.GET)
    @ApiOperation(value = "hello", notes = "notes")
    public String hello(){
        return "hello";
    }
/*
    @GetMapping("/users")
    @ResponseStatus(HttpStatus.OK)
    public Object getUsers(){
        return mUserInfos;
    }

    @GetMapping("/users/{id}")
    @ResponseStatus(HttpStatus.OK)
    public Object getUser(@PathVariable("id") int id){
        for (int i =0; i < mUserInfos.size();i++){
            if (mUserInfos.get(i).id == id){
                return mUserInfos.get(id);
            }
        }
        return null;
    }

    @PostMapping("/users")
    @ResponseStatus(HttpStatus.CREATED)
    public Object addUser(@RequestBody UserInfo userInfo){
        mUserInfos.add(userInfo);
        return userInfo;
    }

    @PutMapping("/users/{id}")
    @ResponseStatus(HttpStatus.CREATED)
    public Object editUser(@PathVariable("id") int id, @RequestBody UserInfo userInfo){
        for (int i = 0; i < mUserInfos.size(); i++){
            if (mUserInfos.get(i).id == id){
                mUserInfos.set(i, userInfo);
                return userInfo;
            }
        }
        mUserInfos.add(userInfo);
        return userInfo;
    }*/
}
