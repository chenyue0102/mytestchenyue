package com.example.demo.config.handler;

import com.example.demo.annotation.TokenToUser;
import com.example.demo.entity.AccessToken;
import com.example.demo.util.Result;
import com.example.demo.util.TokenUtil;
import org.springframework.core.MethodParameter;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.support.WebDataBinderFactory;
import org.springframework.web.context.request.NativeWebRequest;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.method.support.ModelAndViewContainer;

@Component
public class TokenToUserMethodArguentResolver implements HandlerMethodArgumentResolver {
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

            if (null != token && TokenUtil.checkAccessToken(token)){
                AccessToken accessToken = TokenUtil.convert2AccessToken(token);
                return accessToken;
            }else{
                throw new Exception("check token failed");
            }
        }
        return null;
    }
}
