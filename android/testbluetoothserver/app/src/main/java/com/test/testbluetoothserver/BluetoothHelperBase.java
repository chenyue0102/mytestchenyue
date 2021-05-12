package com.test.testbluetoothserver;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattServer;
import android.bluetooth.BluetoothGattServerCallback;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.AdvertiseCallback;
import android.bluetooth.le.AdvertiseData;
import android.bluetooth.le.AdvertiseSettings;
import android.bluetooth.le.BluetoothLeAdvertiser;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.ParcelUuid;
import android.util.Log;

import com.test.testbluetoothserver.util.BleUuidUtils;

import java.nio.ByteBuffer;
import java.util.HashSet;
import java.util.UUID;

public class BluetoothHelperBase {
    private static final String TAG = "bluetooth";
    private BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
    private Context mContext;
    private BroadcastReceiver mBroadcastReceiver;
    private BluetoothManager mBluetoothManager;
    private BluetoothLeAdvertiser mBluetoothLeAdvertiser;
    private BluetoothGattServer mBluetoothGattServer;

    public BluetoothHelperBase(Context context){
        mContext = context;
        mBluetoothManager = (BluetoothManager)mContext.getSystemService(Context.BLUETOOTH_SERVICE);
    }

    public boolean isSupportBluetoothLE(){
        if (null != mBluetoothAdapter){
            return mContext.getPackageManager().hasSystemFeature(PackageManager.FEATURE_BLUETOOTH_LE);
        }else{
            return false;
        }
    }

    public void init(){
        registerReceiver();
        if (!mBluetoothAdapter.isEnabled()){
            mBluetoothAdapter.enable();
        }
    }

    public void destroy(){
        unregisterReceiver();
    }

    /* Current Time Service UUID */
    private static final UUID TIME_SERVICE = BleUuidUtils.fromShortValue(0x1805);
    /* Mandatory Current Time Information Characteristic */
    private static final UUID CURRENT_TIME  = BleUuidUtils.fromShortValue(0x2a2b);
    /* Optional Local Time Information Characteristic */
    private static final UUID LOCAL_TIME_INFO= BleUuidUtils.fromShortValue(0x2a0f);
    /* Mandatory Client Characteristic Config Descriptor */
    private static final UUID CLIENT_CONFIG = BleUuidUtils.fromShortValue(0x2902);

    /**
     * Device Information Service
     */
    private static final UUID SERVICE_DEVICE_INFORMATION = BleUuidUtils.fromShortValue(0x180A);
    private static final UUID CHARACTERISTIC_HID_INFORMATION = BleUuidUtils.fromShortValue(0x2A4A);

    /**
     * HID Service
     */
    private static final UUID SERVICE_BLE_HID = BleUuidUtils.fromShortValue(0x1812);

    /**
     * Battery Service
     */
    private static final UUID SERVICE_BATTERY = BleUuidUtils.fromShortValue(0x180F);

    public void startAdvertising(){
        if (null != mBluetoothLeAdvertiser){
            return;
        }
        mBluetoothLeAdvertiser = mBluetoothManager.getAdapter().getBluetoothLeAdvertiser();
        final AdvertiseSettings settings = new AdvertiseSettings.Builder()
                .setAdvertiseMode(AdvertiseSettings.ADVERTISE_MODE_BALANCED)
                .setConnectable(true)
                .setTimeout(0)
                .setTxPowerLevel(AdvertiseSettings.ADVERTISE_TX_POWER_MEDIUM)
                .build();

        final AdvertiseData data = new AdvertiseData.Builder()
                .setIncludeTxPowerLevel(false)
                .setIncludeDeviceName(true)
                .addServiceUuid(ParcelUuid.fromString(SERVICE_DEVICE_INFORMATION.toString()))
                .addServiceUuid(ParcelUuid.fromString(SERVICE_BLE_HID.toString()))
                .addServiceUuid(ParcelUuid.fromString(SERVICE_BATTERY.toString()))
                .build();

        final AdvertiseData scan = new AdvertiseData.Builder()
                .addServiceUuid(ParcelUuid.fromString(SERVICE_DEVICE_INFORMATION.toString()))
                .addServiceUuid(ParcelUuid.fromString(SERVICE_BLE_HID.toString()))
                .addServiceUuid(ParcelUuid.fromString(SERVICE_BATTERY.toString()))
                .build();
        mBluetoothLeAdvertiser.startAdvertising(settings, data, scan, new AdvertiseCallback(){
            @Override
            public void onStartSuccess(AdvertiseSettings settingsInEffect) {
                super.onStartSuccess(settingsInEffect);
                BluetoothHelperBase.this.onStartSuccess(settingsInEffect);
            }

            @Override
            public void onStartFailure(int errorCode) {
                super.onStartFailure(errorCode);
                BluetoothHelperBase.this.onStartFailure(errorCode);
            }
        });
    }

    private HashSet<BluetoothDevice> mConnectedDevices = new HashSet<>();

    public void startServer(){
        if (null != mBluetoothGattServer){
            return;
        }
        mBluetoothGattServer = mBluetoothManager.openGattServer(mContext, new BluetoothGattServerCallback(){
            @Override
            public void onConnectionStateChange(BluetoothDevice device, int status, int newState) {
                super.onConnectionStateChange(device, status, newState);
                if (null == device){
                    return;
                }
                if (BluetoothProfile.STATE_CONNECTED == newState){
                    Log.e(TAG, "onConnectionStateChange CONNECTED:" + device.getName());
                    mConnectedDevices.add(device);
                }else if (BluetoothProfile.STATE_DISCONNECTED == newState){
                    Log.e(TAG, "onConnectionStateChange DISCONNECTED:" + device.getName());
                    mConnectedDevices.remove(device);
                }
            }

            @Override
            public void onCharacteristicReadRequest(BluetoothDevice device, int requestId, int offset, BluetoothGattCharacteristic characteristic) {
                super.onCharacteristicReadRequest(device, requestId, offset, characteristic);
                if (characteristic.getUuid().equals(CURRENT_TIME)){
                    long time = System.currentTimeMillis();
                    ByteBuffer byteBuffer = ByteBuffer.allocate(8);
                    byteBuffer.putLong(time);
                    mBluetoothGattServer.sendResponse(device, requestId, BluetoothGatt.GATT_SUCCESS, 0, byteBuffer.array());
                }else if (characteristic.getUuid().equals(LOCAL_TIME_INFO)){
                    long time = System.currentTimeMillis();
                    time = time - (time % 86400000);
                    ByteBuffer byteBuffer = ByteBuffer.allocate(8);
                    byteBuffer.putLong(time);
                    mBluetoothGattServer.sendResponse(device, requestId, BluetoothGatt.GATT_SUCCESS, 0, byteBuffer.array());
                }else{
                    Log.e(TAG, "onCharacteristicReadRequest unknown uuid:" + characteristic.getUuid().toString());
                }
            }

            byte[]mDescData = new byte[]{0x41, 0x00};

            @Override
            public void onDescriptorReadRequest(BluetoothDevice device, int requestId, int offset, BluetoothGattDescriptor descriptor) {
                super.onDescriptorReadRequest(device, requestId, offset, descriptor);
                if (descriptor.getUuid().equals(CLIENT_CONFIG)){
                    mBluetoothGattServer.sendResponse(device, requestId, BluetoothGatt.GATT_SUCCESS, 0, mDescData);
                }else{
                    Log.e(TAG, "onDescriptorReadRequest unknown uuid:" + descriptor.getUuid().toString());
                }
            }

            @Override
            public void onDescriptorWriteRequest(BluetoothDevice device, int requestId, BluetoothGattDescriptor descriptor, boolean preparedWrite, boolean responseNeeded, int offset, byte[] value) {
                super.onDescriptorWriteRequest(device, requestId, descriptor, preparedWrite, responseNeeded, offset, value);
                if (descriptor.getUuid().equals(CLIENT_CONFIG)){
                    if (responseNeeded){
                        if (value.length - offset >= mDescData.length){
                            System.arraycopy(value, offset, mDescData, 0, mDescData.length);
                        }
                        mBluetoothGattServer.sendResponse(device, requestId, BluetoothGatt.GATT_SUCCESS, 0, null);
                    }
                }else{
                    Log.e(TAG, "onDescriptorWriteRequest unknown uuid:" + descriptor.getUuid().toString());
                }
            }
        });

        BluetoothGattService bluetoothGattService = new BluetoothGattService(TIME_SERVICE, BluetoothGattService.SERVICE_TYPE_PRIMARY);

        {
            // HID Information
            final BluetoothGattCharacteristic characteristic = new BluetoothGattCharacteristic(
                    CURRENT_TIME,
                    BluetoothGattCharacteristic.PROPERTY_READ | BluetoothGattCharacteristic.PROPERTY_NOTIFY,
                    BluetoothGattCharacteristic.PERMISSION_READ_ENCRYPTED);
            final BluetoothGattDescriptor descriptor = new BluetoothGattDescriptor(
                    CLIENT_CONFIG,
                    BluetoothGattDescriptor.PERMISSION_READ | BluetoothGattDescriptor.PERMISSION_WRITE
            );
            characteristic.addDescriptor(descriptor);
            bluetoothGattService.addCharacteristic(characteristic);
        }
        {
            BluetoothGattCharacteristic characteristic = new BluetoothGattCharacteristic(
                    LOCAL_TIME_INFO,
                    BluetoothGattCharacteristic.PROPERTY_READ,
                    BluetoothGattCharacteristic.PERMISSION_READ_ENCRYPTED
            );
            bluetoothGattService.addCharacteristic(characteristic);
        }
        mBluetoothGattServer.addService(bluetoothGattService);
    }

    public void stopServer(){

    }

    //BroadcastReceiver
    protected void onReceive(Context context, Intent intent){

    }

    //AdvertiseCallback
    protected void onStartSuccess(AdvertiseSettings settingsInEffect) {

    }

    protected void onStartFailure(int errorCode) {

    }

    private void registerReceiver(){
        if (null != mBroadcastReceiver){
            return;
        }
        mBroadcastReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                BluetoothHelperBase.this.onReceive(context, intent);
            }
        };

        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        intentFilter.addAction(BluetoothDevice.ACTION_UUID);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        mContext.registerReceiver(mBroadcastReceiver, intentFilter);
    }

    private void unregisterReceiver(){
        if (null == mBroadcastReceiver){
            return;
        }
        mContext.unregisterReceiver(mBroadcastReceiver);
        mBroadcastReceiver = null;
    }

}
