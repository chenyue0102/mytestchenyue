package com.xixi.observe.service.impl;

import com.xixi.observe.service.RedisService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.redis.core.RedisTemplate;
import org.springframework.stereotype.Service;

import java.util.concurrent.TimeUnit;

@Service
public class RedisServiceImp implements RedisService {
    @Autowired
    private RedisTemplate<String, Object> redisTemplate;

    @Override
    public Object get(String key) {
        return redisTemplate.opsForValue().get(key);
    }

    @Override
    public boolean set(String key, Object value) {
        boolean ret = false;
        try{
            redisTemplate.opsForValue().set(key, value);
            ret = true;
        }catch (Exception e){
            e.printStackTrace();
        }
        return ret;
    }

    @Override
    public boolean set(String key, Object value, long timeout, TimeUnit unit) {
        boolean ret = false;
        try{
            redisTemplate.opsForValue().set(key, value, timeout, unit);
            ret = true;
        }catch (Exception e){
            e.printStackTrace();
        }
        return ret;
    }
}
