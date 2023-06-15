package com.xixi.observe.service.impl;

import com.xixi.observe.dao.LoginUserDao;
import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.LoginUser;
import com.xixi.observe.entity.ServiceRandomResult;
import com.xixi.observe.service.UserService;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.StringUtil;
import com.xixi.observe.util.TokenUtil;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
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
    private MessageDigest sha256Hash;

    public UserServiceImpl() {
        try{
            sha256Hash =  MessageDigest.getInstance("SHA-256");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
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
        boolean findServerRandom = false;
        Iterator<ServerRandomInfo> iterator = serverRandomInfoList.iterator();
        while (iterator.hasNext()){
            ServerRandomInfo tmp = iterator.next();
            if (tmp.serverRandom == loginRequest.getServerRandom()){
                iterator.remove();
                findServerRandom = true;
                break;
            }else{
                break;
            }
        }
        if (!findServerRandom){
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }

        String allText = loginUser.getPassword()
                + String.valueOf(loginRequest.getServerRandom())
                + String.valueOf(loginRequest.getClientRandom());
        byte b[] = allText.getBytes();
        byte hash[] = sha256Hash.digest(b);
        String passwordHash = StringUtil.byteArrayToHex(hash);

        if (!passwordHash.equals(loginRequest.getPasswordHash())){
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }
        LoginResult loginResult = new LoginResult();
        loginResult.setAccessToken(TokenUtil.genericAccessToken(loginUser.getId()));
        loginResult.setRefreshToken("refreshtoken");
        return loginResult;
    }
}
