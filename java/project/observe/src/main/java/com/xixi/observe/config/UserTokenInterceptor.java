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
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
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
        boolean ret = false;
        int code = Result.CODE_FAILED;
        String msg = Result.MSG_FAILED;

        do {
            if (!(handler instanceof HandlerMethod)){
                break;
            }
            HandlerMethod handlerMethod = (HandlerMethod)handler;
            String method = request.getMethod();
            if ("GET".equals(method)){
                if (!handlerMethod.hasMethodAnnotation(GetMapping.class)){
                    logger.warn("method failed:GET");
                    code = Result.CODE_METHOD_FAILED;
                    msg = Result.MSG_METHOD_FAILED;
                    break;
                }
            }else if  ("POST".equals(method)){
                if (!handlerMethod.hasMethodAnnotation(PostMapping.class)){
                    logger.warn("method failed:POST");
                    code = Result.CODE_METHOD_FAILED;
                    msg = Result.MSG_METHOD_FAILED;
                    break;
                }
            }else if ("DELETE".equals(method)){
                if (!handlerMethod.hasMethodAnnotation(DeleteMapping.class)){
                    logger.warn("method failed:DELETE");
                    code = Result.CODE_METHOD_FAILED;
                    msg = Result.MSG_METHOD_FAILED;
                    break;
                }
            }else if ("PUT".equals(method)){
                if (!handlerMethod.hasMethodAnnotation(PutMapping.class)){
                    logger.warn("method failed:PUT");
                    code = Result.CODE_METHOD_FAILED;
                    msg = Result.MSG_METHOD_FAILED;
                    break;
                }
            }

            if (!handlerMethod.hasMethodAnnotation(NoAuthorization.class)){
                String token = request.getHeader("token");
                AccessToken accessToken = new AccessToken();
                logger.warn("token:" + token);
                if (null != token && TokenUtil.getInstance().checkAccessTokenAndConvert(token,accessToken)){
                    AccessTokenThreadLocal.set(accessToken);
                }else{
                    logger.warn("check token failed:" + token);
                    code = Result.CODE_TOKEN_FAILED;
                    msg = Result.MSG_TOKEN_FAILED;
                    break;
                }
            }

            ret = true;
        }while (false);
        if (!ret){
            response.setStatus(HttpServletResponse.SC_OK);
            response.setContentType("application/json,charset=UTF-8");
            PrintWriter writer = response.getWriter();
            Result result = new Result(code, msg);
            String json = mGson.toJson(result);
            writer.write(json);
            writer.flush();
        }
        return ret;
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {
        HandlerInterceptor.super.afterCompletion(request, response, handler, ex);
        AccessTokenThreadLocal.remove();
    }
}
