package com.xixi.observe;

import com.xixi.observe.config.RedisConfig;
import com.xixi.observe.service.impl.RedisServiceImp;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.redis.connection.lettuce.LettuceConnectionFactory;
import org.springframework.data.redis.core.RedisTemplate;

@SpringBootTest
public class RedisTest {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    @Autowired
    private RedisServiceImp redisService;

    @Test
    public void testWrite(){
        try{
            String key = "testkey";
            String value = "testvalue";
            redisService.set(key, value);
            Object s = redisService.get(key);
            logger.warn(s.toString());
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
