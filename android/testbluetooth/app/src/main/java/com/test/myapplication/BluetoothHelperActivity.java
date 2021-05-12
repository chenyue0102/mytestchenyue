package com.test.myapplication;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Bundle;
import android.os.ParcelUuid;
import android.text.TextUtils;
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
import java.util.HashSet;
import java.util.List;
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
        findViewById(R.id.btn_le_discovery).setOnClickListener(v->onLEDiscovery());
        findViewById(R.id.btn_stop_discovery).setOnClickListener(v->onStopDiscovery());
        findViewById(R.id.btn_sdp).setOnClickListener(v->onGetSDP());
        findViewById(R.id.btn_bind).setOnClickListener(v->onBind());
        findViewById(R.id.btn_connect).setOnClickListener(v->onConnect());
        findViewById(R.id.btn_le_connect).setOnClickListener(v->onLeConnect());

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
    BluetoothHelper.BluetoothReceiver mBluetoothReceiver = null;
    ArrayList<BluetoothDevice> mBluetoothDeviceFound = new ArrayList<>();
    HashSet<String> mHashAddress = new HashSet<>();
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
        mHashAddress.clear();
        mSelectItem = -1;
        mBluetoothHelper.setScanMode(BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE, 100);
        mBluetoothHelper.startDiscovery();
    }

    BluetoothAdapter.LeScanCallback mLeScanCallback = new BluetoothAdapter.LeScanCallback() {
        @Override
        public void onLeScan(BluetoothDevice device, int rssi, byte[] scanRecord) {
            if (null != device && null != device.getName() && null != device.getAddress()){
                if (!mHashAddress.contains(device.getAddress())){
                    mHashAddress.add(device.getAddress());
                    mAdapter.add(device.getName());
                    mBluetoothDeviceFound.add(device);
                }
            }
        }
    };

    private void onLEDiscovery(){
        mAdapter.clear();
        mBluetoothDeviceFound.clear();
        mHashAddress.clear();
        mSelectItem = -1;
        BluetoothAdapter.getDefaultAdapter().startLeScan(mLeScanCallback);
    }

    private void onStopDiscovery(){
        mBluetoothHelper.cancelDiscovery();
        BluetoothAdapter.getDefaultAdapter().stopLeScan(mLeScanCallback);
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


        }

    }

    private static final UUID TIME_SERVICE = UUID.fromString("00001805-0000-1000-8000-00805F9B34FB");
    private static final UUID CURRENT_TIME = UUID.fromString("00002a2b-0000-1000-8000-00805F9B34FB");
    private static final UUID CLIENT_CONFIG = UUID.fromString("00002902-0000-1000-8000-00805F9B34FB");

    private BluetoothGatt mBluetoothGatt;
    private List<BluetoothGattService> mBluetoothGattService = new ArrayList<>();
    BluetoothGattCallback mBluetoothGattCallback = new BluetoothGattCallback(){
        @Override
        public void onPhyUpdate(BluetoothGatt gatt, int txPhy, int rxPhy, int status) {
            super.onPhyUpdate(gatt, txPhy, rxPhy, status);
        }

        @Override
        public void onPhyRead(BluetoothGatt gatt, int txPhy, int rxPhy, int status) {
            super.onPhyRead(gatt, txPhy, rxPhy, status);
        }

        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            super.onConnectionStateChange(gatt, status, newState);
            if (newState == BluetoothProfile.STATE_CONNECTED){
                gatt.discoverServices();
            }else if (newState == BluetoothProfile.STATE_DISCONNECTED){
                mBluetoothGatt = null;
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            if (status == BluetoothGatt.GATT_SUCCESS){
                mBluetoothGattService = gatt.getServices();
                for (BluetoothGattService bluetoothGattService : mBluetoothGattService){
                    if (bluetoothGattService.getUuid().equals(TIME_SERVICE)){
                        List<BluetoothGattCharacteristic> bluetoothGattCharacteristics = bluetoothGattService.getCharacteristics();
                        for (BluetoothGattCharacteristic bluetoothGattCharacteristic : bluetoothGattCharacteristics){
                            if (bluetoothGattCharacteristic.getUuid().equals(CURRENT_TIME)){
                                List<BluetoothGattDescriptor> bluetoothGattDescriptors = bluetoothGattCharacteristic.getDescriptors();
                                for (BluetoothGattDescriptor bluetoothGattDescriptor : bluetoothGattDescriptors){
                                    if (bluetoothGattDescriptor.getUuid().equals(CLIENT_CONFIG)){
                                        mBluetoothGatt.readDescriptor(bluetoothGattDescriptor);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            super.onCharacteristicRead(gatt, characteristic, status);
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            super.onCharacteristicWrite(gatt, characteristic, status);
        }

        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
            super.onCharacteristicChanged(gatt, characteristic);
        }

        @Override
        public void onDescriptorRead(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status) {
            super.onDescriptorRead(gatt, descriptor, status);
        }

        @Override
        public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status) {
            super.onDescriptorWrite(gatt, descriptor, status);
        }

        @Override
        public void onReliableWriteCompleted(BluetoothGatt gatt, int status) {
            super.onReliableWriteCompleted(gatt, status);
        }

        @Override
        public void onReadRemoteRssi(BluetoothGatt gatt, int rssi, int status) {
            super.onReadRemoteRssi(gatt, rssi, status);
        }

        @Override
        public void onMtuChanged(BluetoothGatt gatt, int mtu, int status) {
            super.onMtuChanged(gatt, mtu, status);
        }
    };
    private void onLeConnect(){
        if (-1 != mSelectItem){
            initReceive();
            BluetoothDevice bluetoothDevice = mBluetoothDeviceFound.get(mSelectItem);
            BluetoothDevice device = BluetoothAdapter.getDefaultAdapter().getRemoteDevice(bluetoothDevice.getAddress());
            if (false && device.getBondState() == BluetoothDevice.BOND_NONE){
                device.createBond();
                mNeedConnect = true;
            }else{
                mBluetoothGatt = device.connectGatt(this, false, mBluetoothGattCallback);
            }
        }
    }

    private boolean mNeedConnect = false;
    private void initReceive(){
        if (null != mBluetoothReceiver){
            return;
        }
        mBluetoothReceiver = new BluetoothHelper.BluetoothReceiver(new BluetoothHelper.BluetoothHelperCallback() {

            @Override
            public void onDiscoveryStarted() {
                //mTip.setText("查找开始");
            }

            @Override
            public void onDiscoveryFinished() {
                //mTip.setText("查找结束");
            }

            @Override
            public void onBluetoothDeviceFound(BluetoothDevice device) {
                if (!TextUtils.isEmpty(device.getName())){
                    if (!mHashAddress.contains(device.getAddress())){
                        mBluetoothDeviceFound.add(device);
                        mHashAddress.add(device.getAddress());
                        mAdapter.add(device.getName() + "   (" + device.getAddress() +  ")");
                    }
                }
            }

            @Override
            public void onBluetoothDeviceUUIDResult(BluetoothDevice device, ParcelUuid[] uuids) {

            }

            @Override
            public void onBluetoothDeviceConnect(BluetoothDevice device, BluetoothSocket bluetoothSocket) {

            }

            @Override
            public void onBluetoothDeviceBondStateChanged(BluetoothDevice device, int bondState, int previousBondState, int reason) {
                Log.e(TAG, "onBluetoothDeviceBondStateChanged：" + " bondState:" + bondState);
                if (bondState == BluetoothDevice.BOND_BONDED){
                    if (mNeedConnect){
                        mNeedConnect = false;
                        mBluetoothGatt = device.connectGatt(BluetoothHelperActivity.this, true, mBluetoothGattCallback);
                    }
                }
            }
        }){
            @Override
            public void onReceive(Context context, Intent intent) {
                super.onReceive(context, intent);
                final String action = intent.getAction();

                if (action.equals(ACTION_GATT_CONNECTED)){
                    BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                }
            }
        };
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        intentFilter.addAction(BluetoothDevice.ACTION_UUID);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        intentFilter.addAction(ACTION_GATT_CONNECTED);
        intentFilter.addAction(ACTION_GATT_DISCONNECTED);
        registerReceiver(mBluetoothReceiver, intentFilter);
    }

    public final static String ACTION_GATT_CONNECTED =
            "com.example.bluetooth.le.ACTION_GATT_CONNECTED";
    public final static String ACTION_GATT_DISCONNECTED =
            "com.example.bluetooth.le.ACTION_GATT_DISCONNECTED";
    public final static String ACTION_GATT_SERVICES_DISCOVERED =
            "com.example.bluetooth.le.ACTION_GATT_SERVICES_DISCOVERED";
    public final static String ACTION_DATA_AVAILABLE =
            "com.example.bluetooth.le.ACTION_DATA_AVAILABLE";
    public final static String EXTRA_DATA =
            "com.example.bluetooth.le.EXTRA_DATA";
}