package com.example.demo.controller;

import com.example.demo.dao.UserDao;
import com.example.demo.entity.User;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import jakarta.annotation.Resource;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.logging.Logger;

@Api(tags = "tag")
@Controller
public class UserController {
    @Resource
    UserDao userDao;
    @ApiOperation(value = "获取用户列表", notes = "")
    @RequestMapping(value = "/queryall", method = RequestMethod.GET)
    public List<User> queryAll(){
        return userDao.findAllUsers();
    }
/*
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

 */
}
