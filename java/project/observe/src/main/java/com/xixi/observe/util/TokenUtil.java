package com.xixi.observe.util;

import com.xixi.observe.entity.AccessToken;
import com.google.gson.Gson;
import com.xixi.observe.entity.RandomToken;
import com.xixi.observe.entity.RefreshToken;
import org.slf4j.LoggerFactory;

import javax.crypto.Cipher;
import java.nio.charset.StandardCharsets;
import java.security.*;
import java.security.interfaces.RSAPrivateCrtKey;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.RSAPublicKeySpec;
import java.util.Arrays;
import java.util.Base64;
import java.util.UUID;
import java.util.logging.Logger;

public class TokenUtil {
    public static final long ACCESS_TOKEN_EXPIRATION_SECOND = 60 * 60 * 24;
    public static final long REFRESH_TOKEN_EXPIRATION_SECOND = 30 * 24 * 60 * 60;

    private static final org.slf4j.Logger logger = LoggerFactory.getLogger(TokenUtil.class);
    private static final TokenUtil instance = new TokenUtil();

    public static TokenUtil getInstance(){
        return instance;
    }

    private long accessTokenExpirationTime = (System.currentTimeMillis() / 1000) + ACCESS_TOKEN_EXPIRATION_SECOND;
    private String uuid = UUID.randomUUID().toString();
    private Gson gson = new Gson();
    private MessageDigest sha256;
    private PublicKey publicKey;
    private PrivateKey privateKey;

    //rsa加密与解密
    private Cipher rsaEncrypt, rsaDecrypt;

    private long refreshTokenExpirationTime = (System.currentTimeMillis() / 1000) + REFRESH_TOKEN_EXPIRATION_SECOND;

    private TokenUtil(){
        try{
            sha256 = MessageDigest.getInstance("SHA-256");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public void setRSAKey(String strPrivateKey, long refreshTokenExpirationTime){
        try{
            PKCS8EncodedKeySpec spec = new PKCS8EncodedKeySpec(Base64.getDecoder().decode(strPrivateKey));
            KeyFactory keyFactory = KeyFactory.getInstance("RSA");
            privateKey = keyFactory.generatePrivate(spec);
            RSAPrivateCrtKey rsaPrivateCrtKey = (RSAPrivateCrtKey)privateKey;
            RSAPublicKeySpec publicKeySpec = new RSAPublicKeySpec(rsaPrivateCrtKey.getModulus(), rsaPrivateCrtKey.getPublicExponent());
            publicKey = keyFactory.generatePublic(publicKeySpec);

            rsaEncrypt = Cipher.getInstance("RSA");
            rsaEncrypt.init(Cipher.ENCRYPT_MODE, privateKey);

            rsaDecrypt = Cipher.getInstance("RSA");
            rsaDecrypt.init(Cipher.DECRYPT_MODE, publicKey);

            this.refreshTokenExpirationTime = refreshTokenExpirationTime;
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    //随机的token
    public String genericRandomToken(long expTime){
        RandomToken randomToken = new RandomToken();
        randomToken.setRandomToken(UUID.randomUUID().toString());
        randomToken.setExpirationTime(expTime);
        String json = gson.toJson(randomToken);

        String str = json + uuid;
        byte[] hash = sha256.digest(str.getBytes(StandardCharsets.UTF_8));

        byte[]jsonBase64 = Base64.getEncoder().encode(json.getBytes(StandardCharsets.UTF_8));
        byte[]hashBase64 = Base64.getEncoder().encode(hash);
        String str1 = new String((jsonBase64));
        String str2 = new String(hashBase64);
        String token = str1 + "." + str2;
        return token;
    }

    public boolean checkRandomToken(String token){
        boolean ret = false;
        do {
            int index = token.indexOf(".");
            if (index < 0){
                break;
            }
            String jsonBase64 = token.substring(0, index);
            byte[]jsonData = Base64.getDecoder().decode(jsonBase64);
            String json = new String(jsonData);
            RandomToken randomToken = gson.fromJson(json, RandomToken.class);
            if (randomToken.getExpirationTime() < System.currentTimeMillis() / 1000){
                break;
            }
            String hashBase64 = token.substring(index + 1);
            byte[]hashData = Base64.getDecoder().decode(hashBase64);
            String str = json + uuid;
            byte[]hashData2 = sha256.digest(str.getBytes(StandardCharsets.UTF_8));
            ret = Arrays.equals(hashData, hashData2);
        }while (false);
        return ret;
    }

    //String = Base64(Json(AccessToken)).Base64(SHA256(Json(AccessToken)+uuid)))
    public String genericAccessToken(int id) {
        AccessToken accessToken = new AccessToken();
        accessToken.setUserId(id);
        accessToken.setExpirationTime(accessTokenExpirationTime);

        String json = gson.toJson(accessToken);
        byte[] jsonBase64 = Base64.getEncoder().encode(json.getBytes(StandardCharsets.UTF_8));

        String str = json + uuid;
        byte[] hash = sha256.digest(str.getBytes(StandardCharsets.UTF_8));
        byte[] hashBase64 = Base64.getEncoder().encode(hash);

        String str1 = new String(jsonBase64);
        String str2 = new String(hashBase64);
        String token = str1 + "." + str2;
        Logger.getGlobal().warning(token);
        return token;
    }

    public boolean checkAccessTokenAndConvert(String token, AccessToken outAccessToken){
        boolean ret = false;
        do{
            int index = token.indexOf(".");
            if (index < 0){
                logger.warn("checkAccessTokenAndConvert not find dot");
                break;
            }
            String jsonBase64 = token.substring(0, index);
            String json = new String(Base64.getDecoder().decode(jsonBase64));
            AccessToken accessToken = gson.fromJson(json, AccessToken.class);
            if ((System.currentTimeMillis() / 1000) > accessToken.getExpirationTime()){
                logger.warn("checkAccessTokenAndConvert expiration");
                break;
            }
            String hashBase64 = token.substring(index + 1);
            byte[]hashData = Base64.getDecoder().decode(hashBase64);
            String str = json + uuid;
            byte[]hashData2 = sha256.digest(str.getBytes(StandardCharsets.UTF_8));
            ret = Arrays.equals(hashData, hashData2);
            if (ret && null != accessToken){
                outAccessToken.setUserId(accessToken.getUserId());
                outAccessToken.setExpirationTime(accessToken.getExpirationTime());
            }else{
                logger.warn("checkAccessTokenAndConvert check failed");
            }
        }while(false);
        return ret;
    }

    public boolean checkAccessToken(String token){
       return checkAccessTokenAndConvert(token, null);
    }

    public AccessToken convert2AccessToken(String token){
        AccessToken accessToken = new AccessToken();
        if (checkAccessTokenAndConvert(token, accessToken)){
            return accessToken;
        }else{
            return null;
        }
    }

    //String=Base64(Json(RefreshToken)).Base64(RSAPrivate(SHA256(Json(RefreshToken))))
    public String genericRefreshToken(int id){
        String token = "";
        try{
            RefreshToken refreshToken = new RefreshToken();
            refreshToken.setExpirationTime(refreshTokenExpirationTime);
            refreshToken.setUserId(id);

            String json = gson.toJson(refreshToken);
            byte[] jsonByte = json.getBytes(StandardCharsets.UTF_8);
            byte[] jsonBase64 = Base64.getEncoder().encode(jsonByte);

            byte[]hashData = sha256.digest(jsonByte);
            byte[] sign = rsaEncrypt.doFinal(hashData);
            byte[] signBase64 = Base64.getEncoder().encode(sign);

            String str1 = new String(jsonBase64);
            String str2 = new String(signBase64);
            token = str1 + "." + str2;
        }catch (Exception e){
            e.printStackTrace();
        }
        return token;
    }

    public boolean checkRefreshTokenAndConvert(String token, RefreshToken outRefreshToken){
        boolean ret = false;
        try{
            do {
                logger.warn("checkRefreshTokenAndConvert token:" + token);
                int index = token.indexOf(".");
                if (index < 0){
                    logger.warn("checkRefreshTokenAndConvert index:" + index);
                    break;
                }
                String jsonBase64 = token.substring(0, index);
                logger.warn("jsonBase64:" + jsonBase64);
                byte[]jsonData = Base64.getDecoder().decode(jsonBase64);
                String json = new String(jsonData);
                logger.warn("json:" + json);
                RefreshToken refreshToken = gson.fromJson(json, RefreshToken.class);
                if ((System.currentTimeMillis() / 1000) > refreshToken.getExpirationTime()){
                    logger.warn("checkRefreshTokenAndConvert timeout");
                    break;
                }
                byte []hash1 = sha256.digest(jsonData);

                String signBase64 = token.substring(index + 1);
                logger.warn("signBase64:" + signBase64);
                byte[]signEncode = Base64.getDecoder().decode(signBase64);
                logger.warn("signEncode:"+String.valueOf(signEncode));
                byte[]signDecode = rsaDecrypt.doFinal(signEncode);
                logger.warn(String.valueOf(signEncode) + String.valueOf(signDecode));
                ret = Arrays.equals(hash1, signDecode);
                if (ret && null != outRefreshToken){
                    outRefreshToken.setUserId(refreshToken.getUserId());
                    outRefreshToken.setExpirationTime(refreshToken.getExpirationTime());
                }
            }while (false);
        }catch (Exception e){
            logger.warn("checkRefreshTokenAndConvert exception");
            e.printStackTrace();
        }
        return ret;
    }

    public boolean checkRefreshToken(String token){
        return checkRefreshTokenAndConvert(token, null);
    }

    public RefreshToken convert2RefreshToken(String token){
        RefreshToken refreshToken = new RefreshToken();
        if (checkRefreshTokenAndConvert(token, refreshToken)){
            return refreshToken;
        }else{
            return null;
        }
    }
}
