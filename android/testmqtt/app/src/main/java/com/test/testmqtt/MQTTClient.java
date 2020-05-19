package com.test.testmqtt;


import android.content.Context;
import android.util.Log;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class MQTTClient {
    private static final String TAG = "MQTTClient";
    public static final int DEFAULT_CONNECT_TIMEOUT_MS = 3000;
    public static final int DEFAULT_KEEP_ALIVE_INTERVAL = 90;
    private MqttAndroidClient mqttAndroidClient;
    private int connectTimeoutMS = DEFAULT_CONNECT_TIMEOUT_MS;
    private int keepAliveInterval = DEFAULT_KEEP_ALIVE_INTERVAL;
    private boolean automaticReconnect = true;
    private boolean cleanSession = true;

    public void setConnectTimeout(int connectTimeoutMS){
        this.connectTimeoutMS = connectTimeoutMS;
    }

    public void open(Context context, String serverURI, String clientId, String userName, char []password)throws Exception{
        close();

        mqttAndroidClient = new MqttAndroidClient(context, serverURI, clientId);
        mqttAndroidClient.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean reconnect, String serverURI) {
                Log.i(TAG, "connectComplete");
            }

            @Override
            public void connectionLost(Throwable cause) {
                Log.i(TAG, "connectionLost");
            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                Log.i(TAG, "messageArrived");
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {
                Log.i(TAG, "deliveryComplete");
            }
        });

        MqttConnectOptions mqttConnectOptions = new MqttConnectOptions();
        mqttConnectOptions.setConnectionTimeout(connectTimeoutMS);
        mqttConnectOptions.setKeepAliveInterval(keepAliveInterval);
        mqttConnectOptions.setAutomaticReconnect(automaticReconnect);
        mqttConnectOptions.setCleanSession(cleanSession);
        mqttConnectOptions.setUserName(userName);
        mqttConnectOptions.setPassword(password);

        mqttAndroidClient.connect(mqttConnectOptions, null, new IMqttActionListener() {
            @Override
            public void onSuccess(IMqttToken asyncActionToken) {
                Log.i(TAG, "connect onSuccess");
            }

            @Override
            public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                Log.i(TAG, "connect onFailure");
            }
        });
    }

    public void close(){
        if (null != mqttAndroidClient){
            mqttAndroidClient.unregisterResources();
            mqttAndroidClient = null;
        }
    }

    public void subscribeToTopic(String topic, int qos) throws Exception{
        mqttAndroidClient.subscribe(topic, qos, null, new IMqttActionListener() {
            @Override
            public void onSuccess(IMqttToken asyncActionToken) {
                Log.i(TAG, "subscribeToTopic onSuccess");
            }

            @Override
            public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                Log.i(TAG, "subscribeToTopic onFailure");
            }
        });
    }

    public void publis(String topic, String text)throws Exception{
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setPayload(text.getBytes());
        mqttAndroidClient.publish(topic, mqttMessage);
    }
}
