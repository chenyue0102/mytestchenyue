package com.example.demo.controller;

import com.example.demo.dao.UserDao;
import com.example.demo.entity.User;
import jakarta.annotation.Resource;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class UserController {
    @Resource
    UserDao userDao;
    @GetMapping("/queryall")
    public List<User> queryAll(){
        return userDao.findAllUsers();
    }

    @GetMapping("/insert")
    public Boolean insert(Integer id, String name){
        User user = new User();
        user.setId(id);
        user.setName(name);
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
}
