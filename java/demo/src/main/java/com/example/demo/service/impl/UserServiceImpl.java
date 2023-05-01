package com.example.demo.service.impl;

import com.example.demo.dao.LoginUserDao;
import com.example.demo.entity.LoginRequest;
import com.example.demo.entity.LoginResult;
import com.example.demo.entity.LoginUser;
import com.example.demo.service.UserService;
import org.apache.commons.codec.binary.Hex;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.MessageDigest;
import java.util.Arrays;
import java.util.logging.Logger;

@Service
public class UserServiceImpl implements UserService {
    @Autowired
    LoginUserDao loginUserDao;

    @Override
    public LoginResult login(LoginRequest loginRequest) {
        LoginResult loginResult = null;
        try{
            Logger.getGlobal().warning("login~~~~~~~~~~~~~~");
            LoginUser loginUser = loginUserDao.getLoginUser(loginRequest.getLoginName());
            Logger.getGlobal().warning("login~~~~~~~~~~~~~~loginUser"+loginUser.getName());
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
            byte []hash = messageDigest.digest(loginUser.getPassword().getBytes());
            byte []hash2 = Hex.decodeHex(loginRequest.getPasswordHash());
            if (!Arrays.equals(hash, hash2)){
                throw new Exception("not equal");
            }
            loginResult = new LoginResult();
            loginResult.accessToken = "access token";
            loginResult.refreshToken = "refresh token";
        }catch (Exception e){
            e.printStackTrace();
        }
        return loginResult;
    }
}
