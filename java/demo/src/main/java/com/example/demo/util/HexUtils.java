package com.example.demo.util;

import org.apache.commons.codec.binary.Hex;

import javax.servlet.http.PushBuilder;
import java.nio.charset.StandardCharsets;

public class HexUtils {
    public static String hex2String(String hex){
        String result="";
        try{
            byte[]bytes = Hex.decodeHex(hex);
            result = new String(bytes, StandardCharsets.UTF_8);
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    public static String string2Hex(String str){
        char[]chars = Hex.encodeHex(str.getBytes(StandardCharsets.UTF_8));
        return String.valueOf(chars);
    }
}
