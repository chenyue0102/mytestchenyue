package com.xixi.observe.config.handler;

import com.xixi.observe.annotation.TokenToUser;
import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.util.Result;
import com.xixi.observe.util.TokenUtil;
import org.springframework.core.MethodParameter;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.support.WebDataBinderFactory;
import org.springframework.web.context.request.NativeWebRequest;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.method.support.ModelAndViewContainer;

@Component
public class TokenResolver implements HandlerMethodArgumentResolver {
    @Override
    public boolean supportsParameter(MethodParameter parameter) {
        if (parameter.hasParameterAnnotation(TokenToUser.class)){
            return true;
        }
        return false;
    }

    @Override
    public Object resolveArgument(MethodParameter parameter, ModelAndViewContainer mavContainer, NativeWebRequest webRequest, WebDataBinderFactory binderFactory) throws Exception {
        if (parameter.getParameterAnnotation(TokenToUser.class) instanceof TokenToUser){
            String token = webRequest.getHeader("token");

            if (null != token && Result.CODE_SUCCESS == TokenUtil.getInstance().checkAccessToken(token)){
                AccessToken accessToken = TokenUtil.getInstance().convert2AccessToken(token);
                return accessToken;
            }else{
                throw new Exception("check token failed");
            }
        }
        return null;
    }
}
