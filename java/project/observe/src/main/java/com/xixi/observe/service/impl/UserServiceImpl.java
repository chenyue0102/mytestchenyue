package com.xixi.observe.service.impl;

import com.xixi.observe.dao.LoginUserDao;
import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.LoginUser;
import com.xixi.observe.entity.ServiceRandomResult;
import com.xixi.observe.service.UserService;
import com.xixi.observe.util.Result;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

@Service
public class UserServiceImpl implements UserService {
    @Autowired
    LoginUserDao loginUserDao;
    static class ServerRandomInfo
    {
        int serverRandom;
        long timestamp;
    }
    private List<ServerRandomInfo> serverRandomInfoList = new LinkedList<>();
    private final Random random = new Random();

    @Override
    public ServiceRandomResult getServiceRandom() {
        int serverRandom = random.nextInt();
        ServiceRandomResult result = new ServiceRandomResult();
        result.setServiceRandom(serverRandom);

        long timestamp = System.currentTimeMillis();
        ServerRandomInfo serverRandomInfo = new ServerRandomInfo();
        serverRandomInfo.serverRandom = serverRandom;
        serverRandomInfo.timestamp = timestamp;
        serverRandomInfoList.add(serverRandomInfo);

        Iterator<ServerRandomInfo> iterator = serverRandomInfoList.iterator();
        while (iterator.hasNext()){
            ServerRandomInfo tmp = iterator.next();
            if (tmp.timestamp + 5000 < timestamp){
                iterator.remove();
            }else{
                break;
            }
        }

        return result;
    }

    @Override
    public LoginResult login(LoginRequest loginRequest) throws ErrorException {
        LoginUser loginUser = loginUserDao.getLoginUser(loginRequest.getLoginName());
        if (null == loginUser){
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }
        LoginResult loginResult = new LoginResult();
        loginResult.setAccessToken("accesstoken");
        loginResult.setRefreshToken("refreshtoken");
        return loginResult;
    }
}
