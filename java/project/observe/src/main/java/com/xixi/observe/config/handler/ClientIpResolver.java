package com.xixi.observe.config.handler;

import com.xixi.observe.annotation.ClientIp;
import org.springframework.core.MethodParameter;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.support.WebDataBinderFactory;
import org.springframework.web.context.request.NativeWebRequest;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.method.support.ModelAndViewContainer;

import javax.servlet.ServletRequest;
import java.net.InetAddress;
import java.net.UnknownHostException;
@Component
public class ClientIpResolver implements HandlerMethodArgumentResolver {
    private static final String[] IP_HEADER_CANDIDATES = {
            "X-Forwarded-For",
            "Proxy-Client-IP",
            "WL-Proxy-Client-IP",
            "HTTP_X_FORWARDED_FOR",
            "HTTP_X_FORWARDED",
            "HTTP_X_CLUSTER_CLIENT_IP",
            "HTTP_CLIENT_IP",
            "HTTP_FORWARDED_FOR",
            "HTTP_FORWARDED",
            "HTTP_VIA",
            "REMOTE_ADDR"
    };

    @Override
    public boolean supportsParameter(MethodParameter parameter) {
        return parameter.hasParameterAnnotation(ClientIp.class)
                && parameter.getParameterType().equals(String.class);
    }

    @Override
    public Object resolveArgument(MethodParameter parameter, ModelAndViewContainer mavContainer, NativeWebRequest webRequest, WebDataBinderFactory binderFactory) throws Exception {
        //取第一个ip
        for (String header : IP_HEADER_CANDIDATES){
            String ipList = webRequest.getHeader(header);
            if (ipList != null && ipList.length() != 0 && !"unknown".equalsIgnoreCase(ipList)){
                return ipList.split(",")[0];
            }
        }

        //没有代理，使用getRemoteAddr获取ip
        String ip = ((ServletRequest)webRequest.getNativeRequest()).getRemoteAddr();

        //如果是本地回环，根据网卡获取ip地址
        if ("127.0.0.1".equals(ip) || "0:0:0:0:0:0:0:1".equals(ip)){
            try{
                InetAddress inetAddress = InetAddress.getLocalHost();
                return inetAddress.getHostAddress();
            }catch (UnknownHostException e){
                e.printStackTrace();
            }
        }
        return ip;
    }
}
