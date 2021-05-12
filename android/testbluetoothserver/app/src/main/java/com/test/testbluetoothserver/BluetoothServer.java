package com.test.testbluetoothserver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattServerCallback;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothServerSocket;
import android.bluetooth.BluetoothSocket;
import android.bluetooth.le.AdvertiseSettings;
import android.content.Context;

import java.util.UUID;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class BluetoothServer {
    public static final UUID MY_UUID = UUID.fromString("1a68fa50-a83b-11e3-9be7-425861b86ab6");
    private AtomicBoolean mExit = new AtomicBoolean();
    private BluetoothServerCallback mBluetoothServerCallback = null;
    private BluetoothServerSocket mBluetoothServerSocket = null;
    private Thread mListeningThread;
    private Context mContext;
    private BluetoothManager mBluetoothManager;

    interface BluetoothServerCallback{
        void onAccept(BluetoothSocketNode node);
    }

    public BluetoothServer(Context context){
        mContext = context;
        mBluetoothManager = (BluetoothManager) mContext.getSystemService(Context.BLUETOOTH_SERVICE);
    }

    public void setCallback(BluetoothServerCallback callback){
        mBluetoothServerCallback = callback;
    }

    public void startServer(){
        mBluetoothManager.openGattServer(mContext, new BluetoothGattServerCallback() {
            @Override
            public void onConnectionStateChange(BluetoothDevice device, int status, int newState) {
                super.onConnectionStateChange(device, status, newState);
            }
        });

    }

    public void stopServer(){

    }

    private static void listeningThread(BluetoothServerSocket bluetoothServerSocket, AtomicBoolean isExit, BluetoothServerCallback callback){
        if (null == bluetoothServerSocket || null == isExit || null == callback){
            return;
        }
        while (true){
            try{
                BluetoothSocket bluetoothSocket = bluetoothServerSocket.accept();
                if (null != bluetoothSocket){
                    BluetoothSocketNode bluetoothSocketNode = new BluetoothSocketNode(bluetoothSocket);
                    callback.onAccept(bluetoothSocketNode);
                }else{
                    if (isExit.get()){
                        break;
                    }
                }
            }catch (Exception e){
                e.printStackTrace();
            }
            if (isExit.get()){
                break;
            }
        }
    }
}
