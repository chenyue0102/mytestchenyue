package com.example.demo;

import com.example.demo.util.TokenUtil;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
public class TokenTest {
    @Test
    public void testGenericAccessToken(){
        String accessToken = TokenUtil.genericAccessToken(1);
        boolean checkToken = TokenUtil.checkAccessToken(accessToken);
    }
}
