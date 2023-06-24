package com.xixi.observe.util;

import com.xixi.observe.entity.AccessToken;

public class AccessTokenThreadLocal {
    private static final ThreadLocal<AccessToken> LOCAL = new ThreadLocal<>();
    private AccessTokenThreadLocal(){

    }

    public static void set(AccessToken accessToken){
        LOCAL.set(accessToken);
    }

    public static AccessToken get(){
        return LOCAL.get();
    }

    public static void remove(){
        LOCAL.remove();
    }
}
