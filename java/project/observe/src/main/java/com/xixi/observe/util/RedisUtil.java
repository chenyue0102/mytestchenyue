package com.xixi.observe.util;

import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Component;

@Component
public class RedisUtil {
    private static final org.slf4j.Logger logger = LoggerFactory.getLogger(RedisUtil.class);

    private static final RedisUtil instance = new RedisUtil();

    public static RedisUtil getInstance(){
        return instance;
    }

    @Autowired
    private RedisTemplate<String, Object> redisTemplate;
    private RedisUtil(){

    }


    public Object get(final String key){
        logger.warn("redis get");
        return redisTemplate.opsForValue().get(key);
    }

    public boolean set(final String key, Object value){
        boolean ret = false;
        try{
            redisTemplate.opsForValue().set(key, value);
            ret = true;
        }catch (Exception e){
            e.printStackTrace();
        }
        return ret;
    }

    public boolean delete(final String key){
        boolean ret = false;
        try{
            redisTemplate.delete(key);
            ret = true;
        }catch (Exception e){
            e.printStackTrace();
        }
        return ret;
    }
}
