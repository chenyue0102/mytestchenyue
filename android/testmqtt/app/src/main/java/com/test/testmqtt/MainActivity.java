package com.test.testmqtt;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;

public class MainActivity extends AppCompatActivity {

    private MQTTClient mqttClient;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        try{
            mqttClient = new MQTTClient();
            String uri = "tcp://107.182.30.19:11883";
            String clientId = "testtest";
            String userName = "test";
            String tmpPassword = "test1234";
            char []password = tmpPassword.toCharArray();

            mqttClient.open(getApplicationContext(), uri, clientId, userName, password);
        }catch (Exception e){
            e.printStackTrace();
        }

        findViewById(R.id.btn_reg_msg).setOnClickListener(view->subscribeToTopic());
        findViewById(R.id.btn_send_msg).setOnClickListener(view->publis());
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
