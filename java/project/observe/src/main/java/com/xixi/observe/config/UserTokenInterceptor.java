package com.xixi.observe.config;

import com.google.gson.Gson;
import com.xixi.observe.annotation.NoAuthorization;
import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.util.AccessTokenThreadLocal;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.TokenUtil;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;
import org.springframework.web.method.HandlerMethod;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
@Component
public class UserTokenInterceptor implements HandlerInterceptor {
    private Gson mGson = new Gson();
    private static final Logger logger = LoggerFactory.getLogger(UserTokenInterceptor.class);

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        if (!(handler instanceof HandlerMethod)){
            return true;
        }
        HandlerMethod handlerMethod = (HandlerMethod)handler;
        if (handlerMethod.hasMethodAnnotation(NoAuthorization.class)){
            return true;
        }
        String token = request.getHeader("token");
        AccessToken accessToken = new AccessToken();
        logger.warn("token:" + token);
        if (null != token && TokenUtil.getInstance().checkAccessTokenAndConvert(token,accessToken)){
            AccessTokenThreadLocal.set(accessToken);
            return true;
        }else{
            logger.warn("check token failed:" + token);
        }
        response.setStatus(HttpServletResponse.SC_OK);
        response.setContentType("application/json,charset=UTF-8");
        PrintWriter writer = response.getWriter();
        Result result = new Result(Result.CODE_TOKEN_FAILED, Result.MSG_TOKEN_FAILED);
        String json = mGson.toJson(result);
        writer.write(json);
        writer.flush();
        return false;
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        HandlerInterceptor.super.afterCompletion(request, response, handler, ex);
        AccessTokenThreadLocal.remove();
    }
}
