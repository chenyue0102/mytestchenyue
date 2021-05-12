package com.test.testbluetoothserver;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;

import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    private BluetoothHelperBase mBluetoothHelperBase = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_server).setOnClickListener(v->onStartServer());

        ActivityCompat.requestPermissions(this, new String[]{
                Manifest.permission.ACCESS_COARSE_LOCATION,
                Manifest.permission.BLUETOOTH,
                Manifest.permission.BLUETOOTH_ADMIN,
        }, 99);
        mBluetoothHelperBase = new BluetoothHelperBase(this);
    }


    private void onStartServer(){
        mBluetoothHelperBase.init();
        mBluetoothHelperBase.startAdvertising();
        mBluetoothHelperBase.startServer();
    }
}