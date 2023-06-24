package com.xixi.observe.service;

import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.ServiceRandomResult;

public interface UserService {

    ServiceRandomResult getServiceRandom(String ip);

    LoginResult login(LoginRequest loginRequest, String ip)throws ErrorException;
}
