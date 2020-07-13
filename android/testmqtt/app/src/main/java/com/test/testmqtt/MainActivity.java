package com.test.testmqtt;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Base64;

import java.nio.charset.Charset;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;

public class MainActivity extends AppCompatActivity {

    private MQTTClient mqttClient;
    public static String macSignature(String text, String secretKey) throws InvalidKeyException, NoSuchAlgorithmException {
        Charset charset = Charset.forName("UTF-8");
        String algorithm = "HmacSHA1";
        Mac mac = Mac.getInstance(algorithm);
        mac.init(new SecretKeySpec(secretKey.getBytes(charset), algorithm));
        byte[] bytes = mac.doFinal(text.getBytes(charset));
        // android的base64编码注意换行符情况, 使用NO_WRAP
        String s = new String(Base64.encode(bytes, Base64.NO_WRAP), charset);
        return s;
    }

    public static class Base{
        String base;
    }
    public static class Child extends Base{
        String child;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        try{
            mqttClient = new MQTTClient();
            mqttClient.open(getApplicationContext(), "tcp://107.182.30.19:11883", "abcd", "robot", "robot".toCharArray());
        }catch (Exception e){
            e.printStackTrace();
        }

        findViewById(R.id.btn_reg_msg).setOnClickListener(view->subscribeToTopic());
        findViewById(R.id.btn_send_msg).setOnClickListener(view->publis());

        new Handler().postDelayed(()->subscribeToTopic(), 1000);
    }

    private void publis(){
        try{
            mqttClient.publis("test/write/ccc", "123456789");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void subscribeToTopic(){
        try{
            mqttClient.subscribeToTopic("test/read/#", 1);
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
