package com.xixi.observe.controller;

import com.xixi.observe.annotation.ClientIp;
import com.xixi.observe.annotation.NoAuthorization;
import com.xixi.observe.entity.*;
import com.xixi.observe.service.ErrorException;
import com.xixi.observe.service.impl.UserEventServiceImp;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import com.xixi.observe.util.AccessTokenThreadLocal;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.TokenUtil;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import javax.naming.Context;
import javax.naming.InitialContext;
import java.util.List;
import java.util.logging.Logger;

@RestController
public class UserController {
    private static final org.slf4j.Logger logger = LoggerFactory.getLogger(TokenUtil.class);
    @Autowired
    UserInfoServiceImpl userInfoService;

    @Autowired
    UserEventServiceImp userEventService;

    @GetMapping("/test")
    @NoAuthorization
    public String test(){
        return "test";
    }

    @GetMapping("inputparam")
    @NoAuthorization
    public String inputparam(){
        //获取系统环境变量
        String env = System.getenv("inputparam");
        if (null == env){
            try{
                //获取tomcat 环境变量
                InitialContext ctx = new InitialContext();
                Context envCtx = (Context)ctx.lookup("java:comp/env");
                String appEnv = (String)envCtx.lookup("inputparam");
                env = appEnv;
            }catch (Exception e){
                e.printStackTrace();
            }
        }

        return env;
    }

    //请求随机数
    @GetMapping("/random")
    @NoAuthorization
    public Result<ServiceRandomResult> getRandom(@ClientIp String ip){
        Logger.getGlobal().warning("clientip:" + ip);
        Result<ServiceRandomResult> result = new Result<>(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        result.setData(userInfoService.getServiceRandom(ip));
        return result;
    }

    @PostMapping("/refreshtoken")
    @NoAuthorization
    public Result<RefreshTokenResult> refreshToken(@RequestBody RefreshTokenRequest request){
        RefreshToken refreshToken = new RefreshToken();
        Result<RefreshTokenResult> result = new Result(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        try{
            logger.warn("refreshToken:" + request.getRefreshToken());
            if (request.getRefreshToken().contains("+")){
                logger.warn("contains +");
            }else{
                logger.warn("not contains +");
            }
            if (TokenUtil.getInstance().checkRefreshTokenAndConvert(request.getRefreshToken(), refreshToken)){
                String newAccessToken = TokenUtil.getInstance().genericAccessToken(refreshToken.getUserId());
                RefreshTokenResult refreshTokenResult = new RefreshTokenResult();
                refreshTokenResult.setAccessToken(newAccessToken);
                result.setData(refreshTokenResult);
            }else{
                result.setCode(Result.CODE_TOKEN_FAILED);
                result.setMsg(Result.MSG_TOKEN_FAILED);
            }
        }catch (Exception e){
            logger.warn("refreshToken exception");
            e.printStackTrace();
            result.setCode(Result.CODE_FAILED);
            result.setMsg(Result.MSG_FAILED);
        }
        return result;
    }

    //RequestBody
    @GetMapping("/login")
    @NoAuthorization
    public Result<LoginResult> login(LoginRequest loginRequest, @ClientIp String ip){
        Result<LoginResult> result = new Result<>(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        try{
            LoginResult loginResult = userInfoService.login(loginRequest, ip);
            result.setData(loginResult);
        }catch (ErrorException e){
            result.setCode(e.getCode());
            result.setMsg(e.getMsg());
        }
        return result;
    }

    @PostMapping("/uploadevent")
    public Result uploadEvent(UserEventRequest userEventRequest){
        Result result = new Result(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        try{
            if (null == userEventRequest){
                throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
            }
            UserEvent userEvent = new UserEvent();
            AccessToken accessToken = AccessTokenThreadLocal.get();
            userEvent.setUserId(accessToken.getUserId());
            userEvent.setEventId(userEventRequest.getEventId());
            userEvent.setTimestamp(userEventRequest.getTimestamp());
            userEvent.setData(userEventRequest.getData());
            if (!userEventService.insertUserEvent(userEvent)){
                throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
            }
        }catch (ErrorException e){
            result.setCode(e.getCode());
            result.setMsg(e.getMsg());
        }
        return result;
    }

    @GetMapping("/finduserevent")
    public Result<List<UserEvent>> findUserEvent(UserEventFindRequest request){
        Result<List<UserEvent>> result = new Result<>(Result.CODE_SUCCESS, Result.MSG_SUCCEEDED);
        try{
            if (null == request){
                throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
            }
            AccessToken accessToken = AccessTokenThreadLocal.get();
            if (null == accessToken){
                throw new ErrorException(Result.CODE_FAILED, Result.MSG_FAILED);
            }
            List<UserEvent> userEvents = userEventService.findUserEvent(request.getUserId(), request.getEventId(), request.getStartTime(), request.getEndTime());
            result.setData(userEvents);
        }catch (ErrorException e){
            result.setCode(e.getCode());
            result.setMsg(e.getMsg());
        }
        return result;
    }

}
