package com.test.testbluetoothserver;

import android.bluetooth.BluetoothSocket;

public class BluetoothSocketNode {
    private BluetoothSocket mBluetoothSocket;
    private Thread mThread;

    interface BluetoothSocketNodeCallback{
        void onDisconnect();
        void onReceive();
    }

    public BluetoothSocketNode(BluetoothSocket bluetoothSocket){
        mBluetoothSocket = bluetoothSocket;
    }

    public void startProcess(){

    }


}
