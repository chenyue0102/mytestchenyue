package com.example.demo.service;

import com.example.demo.entity.LoginRequest;
import com.example.demo.entity.LoginResult;

public interface UserService {
    LoginResult login(LoginRequest loginRequest);
}
