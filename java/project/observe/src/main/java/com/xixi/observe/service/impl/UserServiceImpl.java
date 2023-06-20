package com.xixi.observe.service.impl;

import com.xixi.observe.dao.LoginUserDao;
import com.xixi.observe.entity.LoginRequest;
import com.xixi.observe.entity.LoginResult;
import com.xixi.observe.entity.LoginUser;
import com.xixi.observe.entity.ServiceRandomResult;
import com.xixi.observe.service.ErrorException;
import com.xixi.observe.service.UserService;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.StringUtil;
import com.xixi.observe.util.TokenUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.security.MessageDigest;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

@Service
public class UserServiceImpl implements UserService {
    private static final int SERVER_RANDOM_TIMEOUT_MS = 5000 * 5000;
    private static final Logger logger = LoggerFactory.getLogger(UserServiceImpl.class);

    @Autowired
    LoginUserDao loginUserDao;

    static class ServerRandomInfo
    {
        String serverRandom;
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
    public ServiceRandomResult getServiceRandom(String ip) {
        int serverRandom = random.nextInt();
        ServiceRandomResult result = new ServiceRandomResult();
        result.setServiceRandom(String.valueOf(serverRandom) + ip);

        long timestamp = System.currentTimeMillis();
        ServerRandomInfo serverRandomInfo = new ServerRandomInfo();
        serverRandomInfo.serverRandom = result.getServiceRandom();
        serverRandomInfo.timestamp = timestamp;
        serverRandomInfoList.add(serverRandomInfo);

        Iterator<ServerRandomInfo> iterator = serverRandomInfoList.iterator();
        while (iterator.hasNext()){
            ServerRandomInfo tmp = iterator.next();
            if (tmp.timestamp + SERVER_RANDOM_TIMEOUT_MS < timestamp){
                logger.warn("remove:" + tmp.serverRandom);
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
            logger.warn("null == loginUser");
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }
        boolean findServerRandom = false;
        Iterator<ServerRandomInfo> iterator = serverRandomInfoList.iterator();
        while (iterator.hasNext()){
            ServerRandomInfo tmp = iterator.next();
            if (tmp.serverRandom.equals(loginRequest.getServerRandom())){
                iterator.remove();
                findServerRandom = true;
                break;
            }else{
                break;
            }
        }
        if (!findServerRandom){
            logger.warn("！findServerRandom" + loginRequest.getServerRandom());
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }

        String allText = loginUser.getPassword()
                + String.valueOf(loginRequest.getServerRandom())
                + String.valueOf(loginRequest.getClientRandom());

        logger.warn("alltext:" + allText);
        byte b[] = allText.getBytes();
        byte hash[] = sha256Hash.digest(b);
        String passwordHash = StringUtil.byteArrayToHex(hash);

        if (!passwordHash.equals(loginRequest.getPasswordHash())){
            logger.warn("！passwordHash" + passwordHash + " "+loginRequest.getPasswordHash());
            throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
        }
        LoginResult loginResult = new LoginResult();
        loginResult.setAccessToken(TokenUtil.getInstance().genericAccessToken(loginUser.getId()));
        loginResult.setRefreshToken(TokenUtil.getInstance().genericRefreshToken(loginUser.getId()));
        return loginResult;
    }
}
