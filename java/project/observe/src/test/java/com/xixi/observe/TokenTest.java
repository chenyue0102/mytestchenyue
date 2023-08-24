package com.xixi.observe;

import com.xixi.observe.dao.PrivateKeyDao;
import com.xixi.observe.entity.AccessToken;
import com.xixi.observe.entity.PrivateKey;
import com.xixi.observe.entity.RefreshToken;
import com.xixi.observe.service.impl.UserInfoServiceImpl;
import com.xixi.observe.util.TokenUtil;
import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import java.sql.Timestamp;

@SpringBootTest
public class TokenTest {
    private static final Logger logger = LoggerFactory.getLogger(UserInfoServiceImpl.class);
    private static final String privateKey = "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDGS8la6Hu3h/Ny\n" +
            "+ezt1GYjG1msroBTOHA6TJP6Ed2yczgaahG2HPSinJyQ1aBQpjarVsljIqPuVRrY\n" +
            "XH14GLuF1Kh1k4Talp+l5rWaDbdUAqgirsAwEzIN3n9TZnWHdf/8oitkN2rjHdP5\n" +
            "0ac/wTOXPhn63v2ZkLHoSEhit0hCDmMUSD8CGyounMHAWERTz/D2T5d/VCgkRGCq\n" +
            "IT7gkqFBRkE4lUvM+Tbp6+ynqZkldCTy/LE3z+dqH9ECpQzU8eTCgABAHpbninBa\n" +
            "kSkLgjm0aCz4fpVon4NhGaDirfU72fTKmSfSvPbrEqgf9fc7suapX4n4PEd4y5i1\n" +
            "D715Mn7tAgMBAAECggEAKXFB3BS99Hm+jL9Ef+EV1oz7BR60NZBUTi7ed1NADvFL\n" +
            "HqQf3vx2uTx7cT6gYnKWduEstiIRejhBo8nStCSRHnN3IJmL2MZFh93rgs6Oi8mB\n" +
            "W7xDcNi2K5VebW76rayg6yr2YBu/5EcB3BJvvqCReHCza82qWSuXLvlaXX06Jgmu\n" +
            "o3RTL7zEKvvp/3Fb1yyJXkYjugR20wu8kU9OqlvDA6ijiO9rX5ogVRnDRUP/VZZ4\n" +
            "Hdl/BBwdIIaTW4ZyvfiXVuA7BuETb9OFxaaT45hZGhYv8TA1eRFWiVpXtgwbWyPi\n" +
            "HXQXIejLIT6SgbKCkIxOyVCHkUusJnXQXn2u33sGIQKBgQDNmSnyAwP7HR7UtnUy\n" +
            "yoR7BQYWSGPfuQos657+WC0tnhMVZQKjdLLDzTNvDXtjKsmhhk2v7uYHWJw2zQqt\n" +
            "uw195A9E/AzByZ30l6KhB1t+QdHGwdJ8DGwaNV+9HcX1tIGyMprubL4dKx0VhbNz\n" +
            "JWz5I96YklcuA8og3JgA3Y1HIQKBgQD26Fn0KLXt5PIyEyyYuEoxkkE6v4yOwrd8\n" +
            "zzTcDcwBKfhTM5BVjffw8ABwDRNkh/YIkMSwRyZJwGlzqICRn40x+HYDbstbxS1S\n" +
            "58J45G8DqOpigXzeokerYOmSpRMvPIWfPcF/OMGiMjOaGg+ZFIEuFMLOWN4m+Pdq\n" +
            "crXsPOLaTQKBgAmNdUJ2W2f+eWE+vQFIIZGpsRe181YAvfVKWU/N/wNgldhnohDA\n" +
            "KlIopZwiTzpTUZz8pX1oJy3uMwvkyPs7dqwDvaXh5CHY4UrtBLRgqCKcokeO193F\n" +
            "ofwxwKoDyR/abDBAY6xyRv8J8sb+OFFASujkfsIuAnjz2h9ewH1Bzf+hAoGBAN2S\n" +
            "TYcqMXk3B5GgW1kBqLMriJXr53sFihva5pjDWNuCinI/x7q/GE2DUyE62rhQup2d\n" +
            "LKT0dIuiu/8qq5YDFHZPfbg+6QeFvtKzYHWUqXsjTpLvmNtBzgchhPowYTL2oQLy\n" +
            "LH66tCmV23DjCjRZjkOIJfl/Dnzy1zUTk+ZYDUvRAoGALHjeVqE90vTbUERboiY9\n" +
            "GF4hRW367+4ZrYB3/ZOXZV7N0essyNA02cBCW1GPitWIQ1uY1dW0C+N6Nq8vPuRA\n" +
            "35svEdV+sMILjcq8jpH8XV0LvbazPhgXsHj7QDn8fTuG+miN6iT0TiwG0K23hTa8\n" +
            "yIeLpS+CnowKVxm34pHZfkU=";
    @Test void testReadRSAKey(){
        String tmpPrivateKey = privateKey.replaceAll("\n", "");
        TokenUtil.getInstance().setRSAKey(tmpPrivateKey, 1000);
    }

    @Test
    public void testAccessToken(){
        String tmpPrivateKey = privateKey.replaceAll("\n", "");
        TokenUtil.getInstance().setRSAKey(tmpPrivateKey, 1000);

        String str = TokenUtil.getInstance().genericAccessToken(1);
        AccessToken accessToken = new AccessToken();
        int checkToken = TokenUtil.getInstance().checkAccessTokenAndConvert(str, accessToken);
        logger.warn("check:" + String.valueOf(checkToken));
    }

    @Test void testRefreshToken(){
        String tmpPrivateKey = privateKey.replaceAll("\n", "");
        TokenUtil.getInstance().setRSAKey(tmpPrivateKey, 1000);

        String str = TokenUtil.getInstance().genericRefreshToken(1);
        RefreshToken refreshToken = new RefreshToken();
        int checkToken = TokenUtil.getInstance().checkRefreshToken(str);
        logger.warn("check:" + String.valueOf(checkToken));
    }

    @Autowired
    PrivateKeyDao privateKeyDao;

    @Test
    void testReadToken(){
        long l = 1577808000;//2020-1-1 0:0:0
        //long l = 1580486400;//2020-2-1 0:0:0
        l *= 1000;
        Timestamp enableTime = new Timestamp(l);
        PrivateKey privateKey1 = privateKeyDao.getPrivateKey(enableTime, enableTime);
        logger.warn("token:" + privateKey1.getPrivateKey()
        + "enable:" + privateKey1.getEnableTime()
        + "exp:" + privateKey1.getExpiration());
    }

    @Test
    void testRefreshToken2(){
        long l = 1577808000;//2020-1-1 0:0:0
        //long l = 1580486400;//2020-2-1 0:0:0
        l *= 1000;
        Timestamp enableTime = new Timestamp(l);
        PrivateKey privateKey1 = privateKeyDao.getPrivateKey(enableTime, enableTime);
        String tmp = privateKey1.getPrivateKey().replaceAll("\n", "");
        TokenUtil.getInstance().setRSAKey(tmp, privateKey1.getExpiration().getTime() / 1000);
        String token = "eyJ1c2VySWQiOjEsImV4cGlyYXRpb25UaW1lIjoxNzA0MDM4NDAwMDAwfQ==.TTFFVs/0882zcBgS4HnGS0T5fIYS/rg9oEWJYlJhIJUBmqszJqQbrUp8I/D+Rv1IhItfzF6E8dUKPnRLv+9fie01IQ3VrXPAyniLdK+MCq012JmCWn4qAnQkaOE0uNR1sj27egWfXqufIGYESomoSgW7kK4LRb6hQMclk22Nokv5BhRypFu4zW+Q+uHlhjNpoxXAg1pDeJhLS4aiq92sd7/a63xuHuWxINp3F84luTg0wmMlR9p/IfzzqO/d0T5Gca6tp8fTUCb4iSicgGG4rehCsW09QAnGtfoCjX7U+MOueHvJum60XzDU8g/LiVy1gFJbqA1anNW8h9DuQU46Rw==";
        RefreshToken refreshToken = TokenUtil.getInstance().convert2RefreshToken(token);
        logger.warn(refreshToken.toString());
    }

    @Test
    void verifyAccessToken(){
        String refreshToken = "eyJ1c2VySWQiOjEsImV4cGlyYXRpb25UaW1lIjoxNzA0MDM4NDAwMDAwfQ==.TTFFVs/0882zcBgS4HnGS0T5fIYS/rg9oEWJYlJhIJUBmqszJqQbrUp8I/D+Rv1IhItfzF6E8dUKPnRLv+9fie01IQ3VrXPAyniLdK+MCq012JmCWn4qAnQkaOE0uNR1sj27egWfXqufIGYESomoSgW7kK4LRb6hQMclk22Nokv5BhRypFu4zW+Q+uHlhjNpoxXAg1pDeJhLS4aiq92sd7/a63xuHuWxINp3F84luTg0wmMlR9p/IfzzqO/d0T5Gca6tp8fTUCb4iSicgGG4rehCsW09QAnGtfoCjX7U+MOueHvJum60XzDU8g/LiVy1gFJbqA1anNW8h9DuQU46Rw==";


        String accessToken = "eyJ1c2VySWQiOjEsImV4cGlyYXRpb25UaW1lIjoxNjg3NTEyOTc3fQ==.7uy3/agstu738mhTBmMWmIvJHGnmv00/rETTB0BrZkk=";

    }
    // "accessToken": "eyJ1c2VySWQiOjEsImV4cGlyYXRpb25UaW1lIjoxNjg3NTA5MTI5fQ==.eYCZ1TYM0rEIo+yaoc7eInfMSQ3WI2Qv2UGazpMTdt4=",
    // "refreshToken":

    @Test
    void testRandomToken(){
        long exp = (System.currentTimeMillis() / 1000) + 10;
        String str = TokenUtil.getInstance().genericRandomToken(exp);
        logger.warn("token:" + str);
        int check = TokenUtil.getInstance().checkRandomToken(str);
        logger.warn("check:" + check);
    }

    @Test
    void testAccessToken2(){
        String token = "eyJ1c2VySWQiOjEsImV4cGlyYXRpb25UaW1lIjoxNjkwNzkzMDQ4fQ==.L//ZimiVzX6AKFzkp0xmqF8rmF8hmVPYbHxDtVcHraU=";
        AccessToken accessToken = new AccessToken();
        TokenUtil.getInstance().checkAccessTokenAndConvert(token, accessToken);
    }

    @Test
    void testGetRefreshToken(){
        String refreshToken = TokenUtil.getInstance().genericRefreshToken(1);
        RefreshToken refreshToken1 = new RefreshToken();
        int b = TokenUtil.getInstance().checkRefreshTokenAndConvert(refreshToken, refreshToken1);
        logger.warn(refreshToken);
    }
}