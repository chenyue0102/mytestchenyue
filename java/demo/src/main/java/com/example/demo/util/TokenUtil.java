package com.example.demo.util;

import com.example.demo.entity.AccessToken;
import com.fasterxml.jackson.databind.ser.Serializers;
import com.google.gson.Gson;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.Arrays;
import java.util.Base64;
import java.util.UUID;
import java.util.logging.Logger;

public class TokenUtil {
    public static final long EXPIRATION_SECOND = 60 * 60 * 24;
    private static long expirationTime = (System.currentTimeMillis() / 1000) + EXPIRATION_SECOND;
    private static String uuid = "87cb28bf-f183-4c8f-acd1-8aa9c7dbb784";//UUID.randomUUID().toString();
    private static Gson gson = new Gson();
    private static MessageDigest sha256;

    static {
        try {
            sha256 = MessageDigest.getInstance("SHA-256");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //base64(json+uuid).base64(hash)
    public static String genericAccessToken(int id) {
        AccessToken accessToken = new AccessToken();
        accessToken.setUserId(id);
        accessToken.setExpirationTime(expirationTime);
        String json = gson.toJson(accessToken);
        String str = json + uuid;
        byte[] hash = sha256.digest(str.getBytes(StandardCharsets.UTF_8));
        byte[] hashBase64 = Base64.getEncoder().encode(hash);
        byte[] jsonBase64 = Base64.getEncoder().encode(json.getBytes(StandardCharsets.UTF_8));
        String str1 = new String(jsonBase64);
        String str2 = new String(hashBase64);
        String token = str1 + "." + str2;
        Logger.getGlobal().warning(token);
        return token;
    }

    public static boolean checkAccessToken(String token){
        boolean ret = false;
        try{
            int index = token.indexOf(".");
            if (index < 0){
                throw new Exception("not find dot");
            }
            String jsonBase64 = token.substring(0, index);
            String json = new String(Base64.getDecoder().decode(jsonBase64));
            AccessToken accessToken = gson.fromJson(json, AccessToken.class);
            if ((System.currentTimeMillis() / 1000) > accessToken.getExpirationTime()){
                throw new Exception("expiration");
            }
            String hashBase64 = token.substring(index + 1);
            byte[]hashData = Base64.getDecoder().decode(hashBase64);
            String str = json + uuid;
            byte[]hashData2 = sha256.digest(str.getBytes(StandardCharsets.UTF_8));
            ret = Arrays.equals(hashData, hashData2);
        }catch (Exception e){
            e.printStackTrace();
        }
        return ret;
    }

    public static AccessToken convert2AccessToken(String token){
        AccessToken accessToken = null;
        try{
            int index = token.indexOf(".");
            if (index < 0){
                throw new Exception("not find dot");
            }
            String jsonBase64 = token.substring(0, index);
            String json = new String(Base64.getDecoder().decode(jsonBase64));
            accessToken = gson.fromJson(json, AccessToken.class);
        }catch (Exception e){
            e.printStackTrace();
        }
        return accessToken;
    }
}
