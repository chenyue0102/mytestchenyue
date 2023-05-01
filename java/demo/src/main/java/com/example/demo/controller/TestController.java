package com.example.demo.controller;

import com.example.demo.dao.UserDao;
import com.example.demo.entity.LoginRequest;
import com.example.demo.entity.LoginResult;
import com.example.demo.entity.User;
import com.example.demo.service.impl.UserServiceImpl;
import com.example.demo.util.Result;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.util.logging.Logger;


@RestController
public class TestController {
    @GetMapping("/test")
    public String test(){
        return "test";
    }


    @Resource
    UserDao userDao;

    @ApiOperation(value = "获取用户列表", notes = "")
    @RequestMapping(value = "/queryall", method = RequestMethod.GET)
    public List<User> queryAll(){
        return userDao.findAllUsers();
    }

    @GetMapping("/insert")
    public Boolean insert(Integer id, String name){
        User user = new User();
        user.setId(id);
        user.setName(name);
        Logger.getGlobal().warning("id:" + String.valueOf(id) + " name:" + name);
        return userDao.insertUser(user) > 0;
    }

    @GetMapping("/update")
    public Boolean update(Integer id, String name){
        User user = new User();
        user.setId(id);
        user.setName(name);
        return userDao.updateUser(user) > 0;
    }

    @GetMapping("/delete")
    public Boolean delete(Integer id){
        return userDao.deleteUser(id) > 0;
    }

    @Autowired
    UserServiceImpl userService;
    @PostMapping("/login")
    public Result<LoginResult> login(LoginRequest loginRequest){
        Result<LoginResult> resultResult = new Result<>();
        resultResult.setData(userService.login(loginRequest));
        return resultResult;
    }
}
