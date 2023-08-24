package com.xixi.observe.service.impl;

import com.xixi.observe.dao.UserInfoDao;
import com.xixi.observe.entity.*;
import com.xixi.observe.service.ErrorException;
import com.xixi.observe.service.UserInfoService;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.StringUtil;
import com.xixi.observe.util.TokenUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.MessageDigest;

@Service
public class UserInfoServiceImpl implements UserInfoService {
    private static final int SERVER_RANDOM_TIMEOUT_SECOND = 10;
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);

    @Autowired
    UserInfoDao userInfoDao;

    private MessageDigest sha512Hash;

    public UserInfoServiceImpl() {
        try{
            sha512Hash =  MessageDigest.getInstance("SHA-512");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    @Override
    public ServiceRandomResult getServiceRandom(String ip) {
        ServiceRandomResult result = new ServiceRandomResult();
        long expTime = (System.currentTimeMillis() / 1000) + SERVER_RANDOM_TIMEOUT_SECOND;
        result.setServiceRandom(TokenUtil.getInstance().genericRandomToken(expTime));
        return result;
    }

    @Override
    public LoginResult login(LoginRequest loginRequest, String ip) throws ErrorException {
        logger.warn("login ip:" + ip + " loginName:" + loginRequest.getLoginName());
        LoginUser loginUser = userInfoDao.getLoginUser(loginRequest.getLoginName());
        if (null == loginUser){
            logger.warn("null == loginUser");
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }

        if (Result.CODE_SUCCESS != TokenUtil.getInstance().checkRandomToken(loginRequest.getServerRandom())){
            logger.warn("checkRandomToken failed");
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }

        String allText = loginUser.getPassword()
                + String.valueOf(loginRequest.getServerRandom())
                + String.valueOf(loginRequest.getClientRandom());

        logger.warn("alltext:" + allText);
        byte b[] = allText.getBytes();
        byte hash[] = sha512Hash.digest(b);
        String passwordHash = StringUtil.byteArrayToHex(hash);

        if (!passwordHash.equals(loginRequest.getPasswordHash())){
            logger.warn("！passwordHash" + passwordHash + " "+loginRequest.getPasswordHash());
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }



        LoginResult loginResult = new LoginResult();
        loginResult.setAccessToken(TokenUtil.getInstance().genericAccessToken(loginUser.getUserId()));
        loginResult.setRefreshToken(TokenUtil.getInstance().genericRefreshToken(loginUser.getUserId()));
        return loginResult;
    }

    @Override
    public UserInfo getUserInfo(int userId) {
        return userInfoDao.getUserInfo(userId);
    }
}
