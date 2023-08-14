package com.xixi.observe;

import com.wf.captcha.base.Captcha;
import com.xixi.observe.entity.LoginProperties;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class TestCaptcha {
    private static final Logger logger = LoggerFactory.getLogger(TestCaptcha.class);
    @Autowired
    private LoginProperties loginProperties;

    @Test
    public void TestCaptcha1(){
        Captcha captcha = loginProperties.getCaptcha();
        String text = captcha.text();
        String base64 = captcha.toBase64();
        logger.warn("text:" + text + " base64:" + base64);
    }
}
