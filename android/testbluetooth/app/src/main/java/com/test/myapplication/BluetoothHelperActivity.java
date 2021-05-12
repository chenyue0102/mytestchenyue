package com.test.myapplication;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.graphics.Color;
import android.os.Bundle;
import android.os.ParcelUuid;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import com.inuker.bluetooth.library.BluetoothClient;
import com.inuker.bluetooth.library.beacon.Beacon;
import com.inuker.bluetooth.library.connect.response.BleConnectResponse;
import com.inuker.bluetooth.library.connect.response.BleReadResponse;
import com.inuker.bluetooth.library.connect.response.BleReadRssiResponse;
import com.inuker.bluetooth.library.model.BleGattCharacter;
import com.inuker.bluetooth.library.model.BleGattDescriptor;
import com.inuker.bluetooth.library.model.BleGattProfile;
import com.inuker.bluetooth.library.model.BleGattService;

import java.util.ArrayList;
import java.util.UUID;

public class BluetoothHelperActivity extends AppCompatActivity {
    private static final String TAG = "tag";
    private ListView mLVDeives;
    private ArrayAdapter<String> mAdapter = null;
    private int mSelectItem = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth_helper);
        findViewById(R.id.btn_discovery).setOnClickListener(v->onDiscovery());
        findViewById(R.id.btn_stop_discovery).setOnClickListener(v->onStopDiscovery());
        findViewById(R.id.btn_sdp).setOnClickListener(v->onGetSDP());
        findViewById(R.id.btn_bind).setOnClickListener(v->onBind());
        findViewById(R.id.btn_connect).setOnClickListener(v->onConnect());

        mLVDeives = findViewById(R.id.lv_devices);
        mAdapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1){
            @NonNull
            @Override
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                if (position == mSelectItem){
                    view.setBackgroundColor(Color.GREEN);
                }else{
                    view.setBackgroundColor(Color.WHITE);
                }
                return view;
            }
        };
        mAdapter.setNotifyOnChange(true);
        mLVDeives.setAdapter(mAdapter);
        mLVDeives.setOnItemClickListener((parent, view, position, id) -> {
            mSelectItem = position;
            mAdapter.notifyDataSetChanged();
        });
    }

    ArrayList<BluetoothDevice> mBluetoothDeviceFound = new ArrayList<>();
    BluetoothHelper mBluetoothHelper = new BluetoothHelper(this, new BluetoothHelper.BluetoothHelperCallback() {
        @Override
        public void onDiscoveryStarted() {
            Log.e(TAG, "onDiscoveryStarted");
        }

        @Override
        public void onDiscoveryFinished() {
            Log.e(TAG, "onDiscoveryFinished");
            /*
            if (!mBluetoothDeviceFound.isEmpty()){
                BluetoothDevice device = mBluetoothDeviceFound.remove(0);
                mBluetoothHelper.fetchUuidsWithSdp(device);
            }
             */
        }

        @Override
        public void onBluetoothDeviceFound(BluetoothDevice device) {
            if (null != device.getName()){
                Log.e(TAG, "device name:" + device.getName() + " address:" + device.getAddress());
                mAdapter.add(device.getName());
                mBluetoothDeviceFound.add(device);
            }
        }

        @Override
        public void onBluetoothDeviceUUIDResult(BluetoothDevice device, ParcelUuid[] uuids) {
            Log.e(TAG, "onBluetoothDeviceUUIDResult name:" + device.getName());
            if (null != uuids){
                for (ParcelUuid uuid : uuids){
                    Log.e(TAG, "        " + uuid.toString());
                }
            }
        }

        @Override
        public void onBluetoothDeviceConnect(BluetoothDevice device, BluetoothSocket bluetoothSocket) {
            Log.e(TAG, "onBluetoothDeviceConnect name:" + device.getName());
        }

        @Override
        public void onBluetoothDeviceBondStateChanged(BluetoothDevice device, int bondState, int previousBondState, int reason) {
            Log.e(TAG, "onBluetoothDeviceBondStateChanged name:" + device.getName());
        }
    });

    private void onDiscovery(){
        BluetoothAdapter.getDefaultAdapter().getProfileProxy(this, new BluetoothProfile.ServiceListener() {
            @Override
            public void onServiceConnected(int profile, BluetoothProfile proxy) {
                Log.e(TAG, "onServiceConnected");
            }

            @Override
            public void onServiceDisconnected(int profile) {
                Log.e(TAG, "onServiceDisconnected");
            }
        },  BluetoothProfile.HID_DEVICE);

        if (!mBluetoothHelper.isEnabled()){
            mBluetoothHelper.enable();
        }
        mAdapter.clear();
        mBluetoothDeviceFound.clear();
        mBluetoothHelper.setScanMode(BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE, 100);
        mBluetoothHelper.startDiscovery();
    }

    private void onStopDiscovery(){
        mBluetoothHelper.cancelDiscovery();
    }

    private void onGetSDP(){
        if (-1 != mSelectItem) {
            BluetoothDevice device = mBluetoothDeviceFound.get(mSelectItem);
            mBluetoothHelper.fetchUuidsWithSdp(device);
        }
    }

    private void onBind(){
        if (-1 != mSelectItem){
            BluetoothDevice device = mBluetoothDeviceFound.get(mSelectItem);
            mBluetoothHelper.createBond(device);
        }
    }
    BluetoothClient mClient;
    private void onConnect(){
        if (-1 != mSelectItem) {
            mBluetoothHelper.cancelDiscovery();
            BluetoothDevice device = mBluetoothDeviceFound.get(mSelectItem);
            //mBluetoothHelper.connect(device, BluetoothHelper.HID_PROTOCOL_UUID);
            mClient = new BluetoothClient(this);
            mClient.connect(device.getAddress(), new BleConnectResponse(){
                @Override
                public void onResponse(int code, BleGattProfile data) {
                    Log.e(TAG, "onResponse");
                    UUID hid = UUID.fromString("0000180a-0000-1000-8000-00805f9b34fb");
                    for (BleGattService bleGattService : data.getServices()){
                        if (true||bleGattService.getUUID().equals(hid)){
                            Log.e(TAG, "BleGattService:" + bleGattService.getUUID());
                            for (BleGattCharacter bleGattCharacter : bleGattService.getCharacters()){
                                Log.e(TAG, "  BleGattCharacter:" + bleGattCharacter.getUuid());
                                mClient.read(device.getAddress(), bleGattService.getUUID(), bleGattCharacter.getUuid(), new BleReadResponse() {
                                    @Override
                                    public void onResponse(int code, byte[] data) {
                                        if (0 == code){

                                            Log.e(TAG, "onResponse" + code);
                                            Log.e(TAG, "BleGattService:" + bleGattService.getUUID() + " bleGattCharacter:" + bleGattCharacter.getUuid());
                                        }
                                    }
                                });
                                for (BleGattDescriptor bleGattDescriptor : bleGattCharacter.getDescriptors()){
                                    Log.e(TAG, "    BleGattDescriptor:" + bleGattDescriptor.getmUuid());
                                    mClient.readDescriptor(device.getAddress(),
                                            bleGattService.getUUID(),
                                            bleGattCharacter.getUuid(),
                                            bleGattDescriptor.getmUuid().getUuid(),
                                            new BleReadResponse() {
                                                @Override
                                                public void onResponse(int code, byte[] data) {
                                                    if (null != data){
                                                        Log.e(TAG, "onResponse " + "byte:" + data[0]);
                                                    }else{
                                                        Log.e(TAG, "onResponse data null");
                                                    }
                                                }
                                            });
                                }
                            }
                        }
                    }

                    UUID cha = UUID.fromString("00002a29-0000-1000-8000-00805f9b34fb");
//                    mClient.read(device.getAddress(), hid, cha, new BleReadResponse() {
//                        @Override
//                        public void onResponse(int code, byte[] data) {
//                            Log.e(TAG, "onResponse" + code);
//                        }
//                    });
                    //mClient.readDescriptor(device.getAddress(), hid, cha, new );
                }
            });
            //Beacon beacon = new Beacon(device);

        }

    }
}