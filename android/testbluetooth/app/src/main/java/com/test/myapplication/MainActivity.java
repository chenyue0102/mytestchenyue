package com.test.myapplication;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.app.Person;

import android.Manifest;
import android.app.Instrumentation;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothHidDevice;
import android.bluetooth.BluetoothHidDeviceAppQosSettings;
import android.bluetooth.BluetoothHidDeviceAppSdpSettings;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothSocket;
import android.content.ComponentName;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.graphics.Color;
import android.os.Bundle;
import android.os.ParcelUuid;
import android.os.SystemClock;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import org.jetbrains.annotations.NotNull;

import java.lang.reflect.Method;
import java.lang.reflect.ParameterizedType;
import java.lang.reflect.Type;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.Executor;
import java.util.concurrent.ThreadPoolExecutor;

public class MainActivity extends AppCompatActivity{
    private static final String TAG = "tag";
    private View mViewMouse;
    private View mViewKeyboard;
    private View mViewBluetooth;
    private View mViewHID;
    private TextView mTip;
    private ListView mLVDeives;
    private ArrayAdapter<String> mAdapter = null;
    private int mSelectItem = -1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.BLUETOOTH, Manifest.permission.BLUETOOTH_ADMIN,
                Manifest.permission.WAKE_LOCK, Manifest.permission.FOREGROUND_SERVICE, "android.permission.INJECT_EVENTS"}, 0);

        findViewById(R.id.btn_hid).setOnClickListener(v->showPage(3));
        findViewById(R.id.btn_mouse).setOnClickListener(v->showPage(0));
        findViewById(R.id.btn_keyboard).setOnClickListener(v->showPage(1));
        findViewById(R.id.btn_bluetooth).setOnClickListener(v->{
            Intent intent = new Intent(this, BluetoothHelperActivity.class);
            startActivity(intent);
        });
        findViewById(R.id.btn_discovery_hid).setOnClickListener(v->searchHid());
        findViewById(R.id.btn_connect).setOnClickListener(v->connectHid());
        findViewById(R.id.btn_disconnect).setOnClickListener(v->disconnectHid());
        mTip = findViewById(R.id.tv_tip);
        //findViewById(R.id.btn_discovery).setOnClickListener(v->onDiscovery());
        LinearLayout contarinerKeyboard = findViewById(R.id.container_keyboard);

        int count = contarinerKeyboard.getChildCount();
        for (int i = 0;i < count; i++){
            ViewGroup viewGroup = (ViewGroup)contarinerKeyboard.getChildAt(i);
            setKeyboardTouchListener(viewGroup);
        }
        mViewMouse = findViewById(R.id.container_mouse);
        mViewKeyboard = findViewById(R.id.container_keyboard);
        mViewBluetooth = findViewById(R.id.container_bluetooth);
        mViewHID = findViewById(R.id.container_hid);

        mLVDeives = findViewById(R.id.lv_devices_hid);
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


        View viewMouseMove = findViewById(R.id.view_mouse_move);

        //mouse move
        MouseMoveClickListener.IMouseMoveCallback moveCallback = new MouseMoveClickListener.IMouseMoveCallback(){
            @Override
            public void onMouseMove(int offsetx, int offsety) {
                mScrollableTrackpadMouseReport.dxMsb =  getHighByte((short) offsetx);
                mScrollableTrackpadMouseReport.dxLsb =  getLowByte((short) offsetx);

                mScrollableTrackpadMouseReport.dyMsb =  getHighByte((short) offsety);
                mScrollableTrackpadMouseReport.dyLsb =  getLowByte((short) offsety);
                sendMouseEvent();
            }

            @Override
            public void onMouseMoveStop() {
                mScrollableTrackpadMouseReport.dxMsb =  0;
                mScrollableTrackpadMouseReport.dxLsb =  0;

                mScrollableTrackpadMouseReport.dyMsb =  0;
                mScrollableTrackpadMouseReport.dyLsb =  0;
            }

            @Override
            public void onMouseClick() {
                mScrollableTrackpadMouseReport.leftButton = true;
                sendMouseEvent();
                mScrollableTrackpadMouseReport.leftButton = false;
                sendMouseEvent();
            }
        };
        MouseMoveClickListener mouseMoveListener = new MouseMoveClickListener(moveCallback);
        viewMouseMove.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                return mouseMoveListener.onTouch(v, event);
            }
        });

        //left button
        MouseClickListener.IMouseClickCallback leftMouseClick = new MouseClickListener.IMouseClickCallback(){
            @Override
            public void onMouseDown() {
                mScrollableTrackpadMouseReport.leftButton = true;
                sendMouseEvent();
            }

            @Override
            public void onMouseUp() {
                mScrollableTrackpadMouseReport.leftButton = false;
                sendMouseEvent();
            }

            @Override
            public void onMouseDbClick() {

            }
        };
        MouseClickListener leftMouseClickListener = new MouseClickListener(leftMouseClick);
        View viewLeftMouse = findViewById(R.id.textview_left_button);
        viewLeftMouse.setOnTouchListener(leftMouseClickListener);

        //right button
        MouseClickListener.IMouseClickCallback rightMouseClick = new MouseClickListener.IMouseClickCallback(){
            @Override
            public void onMouseDown() {
                mScrollableTrackpadMouseReport.rightButton = true;
                sendMouseEvent();
            }

            @Override
            public void onMouseUp() {
                mScrollableTrackpadMouseReport.rightButton = false;
                sendMouseEvent();
            }

            @Override
            public void onMouseDbClick() {

            }
        };
        MouseClickListener rightMouseClickListener = new MouseClickListener(rightMouseClick);
        View viewRightMouse = findViewById(R.id.textview_right_button);
        viewRightMouse.setOnTouchListener(rightMouseClickListener);

        //scroll
        MouseMoveListener.IMouseMoveCallback scrollCallback = new MouseMoveListener.IMouseMoveCallback(){
            @Override
            public void onMouseMove(int offsetx, int offsety) {
                mScrollableTrackpadMouseReport.hScroll = (byte)offsetx;
                mScrollableTrackpadMouseReport.vScroll = (byte)offsety;
                sendMouseEvent();
            }

            @Override
            public void onMouseMoveStop() {
                mScrollableTrackpadMouseReport.hScroll = 0;
                mScrollableTrackpadMouseReport.vScroll = 0;
            }
        };
        MouseMoveListener scrollMoveListener = new MouseMoveListener(scrollCallback);
        View viewScroll = findViewById(R.id.textview_scroll);
        viewScroll.setOnTouchListener((v, event) -> scrollMoveListener.onTouch(v, event));

        showPage(3);

        PackageManager pm = getPackageManager();
        ComponentName cn = new ComponentName("com.android.bluetooth","com.android.bluetooth.hid.HidDevService");
        int cs = pm.getComponentEnabledSetting(cn);
        Log.i(TAG, "HID service state" + cs);
        initReceive();
    }

    BluetoothAdapter mBluetoothAdapter = null;
    BluetoothHidDevice mBluetoothHidDevice = null;
    BluetoothDevice mOtherDevice = null;

    ScrollableTrackpadMouseReport mScrollableTrackpadMouseReport = new ScrollableTrackpadMouseReport();

    public byte getHighByte(short n){
        return (byte)((n & 0xFF00) >> 8);
    }

    public byte getLowByte(short n){
        return (byte)(n & 0x00FF);
    }

    void sendMouseEvent(){
        if (null != mBluetoothHidDevice && null != mOtherDevice){
            mBluetoothHidDevice.sendReport(mOtherDevice, ScrollableTrackpadMouseReport.ID, mScrollableTrackpadMouseReport.packByte());
            Log.e(TAG, "sendMouseEvent leftButton:" + mScrollableTrackpadMouseReport.leftButton
                    + " rightButton:" + mScrollableTrackpadMouseReport.rightButton
                    + " lx:" + mScrollableTrackpadMouseReport.dxLsb + " hx:" + mScrollableTrackpadMouseReport.dxMsb
                    + " ly:" + mScrollableTrackpadMouseReport.dyLsb + " hy:" + mScrollableTrackpadMouseReport.dyMsb
                    + " hs" + mScrollableTrackpadMouseReport.hScroll + " vs:" + mScrollableTrackpadMouseReport.vScroll
            );
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull @NotNull String[] permissions, @NonNull @NotNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    BluetoothHelper.BluetoothReceiver mBluetoothReceiver = null;

    private void testg(){
        Type superClass = Student.class.getGenericSuperclass();
        String s1 = ((ParameterizedType)superClass).getActualTypeArguments()[0].getTypeName();
        String s2 = ((ParameterizedType)superClass).getActualTypeArguments()[1].getTypeName();
        Log.e(TAG, "" + superClass.getTypeName() + s1 + s2);
    }
    private void searchHid(){
        testg();
        testsend();
        initReceive();
        mAdapter.clear();
        mBluetoothDeviceFound.clear();
        mHashAddress.clear();
        mSelectItem = -1;

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        mBluetoothAdapter.cancelDiscovery();

        mBluetoothAdapter.startDiscovery();

        int profile = BluetoothProfile.HID_DEVICE;
        boolean result = mBluetoothAdapter.getProfileProxy(this, new BluetoothProfile.ServiceListener(){
            @Override
            public void onServiceConnected(int profile, BluetoothProfile proxy) {
                doServiceConnected(profile, proxy);
            }

            @Override
            public void onServiceDisconnected(int profile) {
                doServiceDisconnected(profile);
            }
        }, profile);
        Log.e(TAG, "onTest :" + result);

    }

    private boolean mNeedConnect =false;

    private void testsend(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                    Instrumentation inst=new Instrumentation();
                    inst.sendPointerSync(MotionEvent.obtain(SystemClock.uptimeMillis(),SystemClock.uptimeMillis(), MotionEvent.ACTION_DOWN, 10, 10, 0));
                    inst.sendPointerSync(MotionEvent.obtain(SystemClock.uptimeMillis(),SystemClock.uptimeMillis(), MotionEvent.ACTION_UP, 10, 10, 0));
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private void initReceive(){
        if (null != mBluetoothReceiver){
            return;
        }
        mBluetoothReceiver = new BluetoothHelper.BluetoothReceiver(new BluetoothHelper.BluetoothHelperCallback() {
            @Override
            public void onDiscoveryStarted() {
                mTip.setText("查找开始");
            }

            @Override
            public void onDiscoveryFinished() {
                mTip.setText("查找结束");
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
                        if (null != mBluetoothHidDevice && null != device){
                            boolean s = mBluetoothHidDevice.connect(device);
                            mTip.setText("准备连接：" + device.getName() + " result:" + s);
                        }
                    }
                }
            }
        });
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothDevice.ACTION_FOUND);
        intentFilter.addAction(BluetoothDevice.ACTION_UUID);
        intentFilter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        intentFilter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        registerReceiver(mBluetoothReceiver, intentFilter);
    }

    private void connectHid(){
        mNeedConnect = false;
        if (-1 != mSelectItem && null != mBluetoothHidDevice){
            mBluetoothAdapter.cancelDiscovery();
            BluetoothDevice bluetoothDevice = mBluetoothDeviceFound.get(mSelectItem);
            if (BluetoothDevice.BOND_NONE == bluetoothDevice.getBondState()){
                boolean s = bluetoothDevice.createBond();
                mTip.setText("准备配对：" + bluetoothDevice.getName() + " result:" + s);
                mNeedConnect = true;
            }else{
                boolean s = mBluetoothHidDevice.connect(bluetoothDevice);
                mTip.setText("准备连接：" + bluetoothDevice.getName() + " result:" + s);
            }
        }
    }

    private void disconnectHid(){
        if (null != mBluetoothHidDevice && null != mOtherDevice){
            mBluetoothHidDevice.disconnect(mOtherDevice);
        }
    }

    KeyboardReport mKeyboardReport = new KeyboardReport();

    private static final int []attrs = {android.R.attr.keycode};
    private void setKeyboardTouchListener(ViewGroup viewGroup){
        int count = viewGroup.getChildCount();
        for (int i = 0; i < count; i++){
            KeyboardView view = (KeyboardView)viewGroup.getChildAt(i);
            final int keycode = view.getKeyCode();
            view.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    switch (event.getAction()){
                        case MotionEvent.ACTION_DOWN:
                            if (KeyboardReport.isCtrlKey(keycode)){
                                mKeyboardReport.setCtrlKey(keycode, true);
                                sendKeyboardEvent();
                            }else{
                                mKeyboardReport.key1 = keycode;
                                sendKeyboardEvent();
                            }
                            break;
                        case MotionEvent.ACTION_UP:
                            if (KeyboardReport.isCtrlKey(keycode)){
                                mKeyboardReport.setCtrlKey(keycode, false);
                                sendKeyboardEvent();
                            }else{
                                mKeyboardReport.reset();
                                sendKeyboardEvent();//send null
                            }
                            break;
                        default:
                            break;
                    }
                    return true;
                }
            });
        }
    }

    void sendKeyboardEvent(){
        if (null != mBluetoothHidDevice && null != mOtherDevice){
            mBluetoothHidDevice.sendReport(mOtherDevice, KeyboardReport.ID, mKeyboardReport.packByte());
            Log.e(TAG, "sendKeyboardEvent leftControl:" + mKeyboardReport.leftControl
                    + " leftShift:" + mKeyboardReport.leftShift
                    + " leftAlt:" + mKeyboardReport.leftAlt
                    + " leftGui:" + mKeyboardReport.leftGui
                    + " rightControl:" + mKeyboardReport.rightControl
                    + " rightShift:" + mKeyboardReport.rightShift
                    + " rightAlt:" + mKeyboardReport.rightAlt
                    + " rightGui:" + mKeyboardReport.rightGui
                    + " key1:" + mKeyboardReport.key1
            );
        }
    }

    int getShift(int keyCode){
        int shift = 0;
        switch (keyCode){
            case KeyEvent.KEYCODE_CTRL_LEFT:
                shift = 0;
                break;
            case KeyEvent.KEYCODE_SHIFT_LEFT:
                shift = 1;
                break;
            case KeyEvent.KEYCODE_ALT_LEFT:
                shift = 2;
                break;
            case KeyEvent.KEYCODE_WINDOW:
                shift = 3;
                break;
            case KeyEvent.KEYCODE_CTRL_RIGHT:
                shift = 4;
                break;
            case KeyEvent.KEYCODE_SHIFT_RIGHT:
                shift = 5;
                break;
            case KeyEvent.KEYCODE_ALT_RIGHT:
                shift = 6;
                break;
            case KeyEvent.KEYCODE_MENU:
                shift = 7;
                break;
            default:
                break;
        }
        return shift;
    }

    public class Person<T,V>{

    }

    public class Student extends Person<String, Integer>{

    }


    private void showPage(int page){
        mViewMouse.setVisibility(0 == page ? View.VISIBLE : View.GONE);
        mViewKeyboard.setVisibility(1 == page ? View.VISIBLE : View.GONE);
        mViewBluetooth.setVisibility(2 == page ? View.VISIBLE : View.GONE);
        mViewHID.setVisibility(3 == page ? View.VISIBLE : View.GONE);
    }

    private ArrayList<BluetoothDevice> mBluetoothDeviceFound = new ArrayList<>();
    private Set<String> mHashAddress = new HashSet<>();


    public void doServiceConnected(int profile, BluetoothProfile proxy) {
        Log.e(TAG, "onServiceConnected profile:" + profile);
        if (proxy instanceof BluetoothHidDevice) {
            mBluetoothHidDevice = (BluetoothHidDevice) proxy;
            BluetoothHidDeviceAppSdpSettings spdRecord = new BluetoothHidDeviceAppSdpSettings("Pixel HID1", "Mobile BController", "test",
                    BluetoothHidDevice.SUBCLASS1_COMBO,
                    MOUSE_KEYBOARD_COMBO);
            BluetoothHidDeviceAppQosSettings qosOut = new BluetoothHidDeviceAppQosSettings(BluetoothHidDeviceAppQosSettings.SERVICE_BEST_EFFORT,
                    800,
                    9,
                    0,
                    11250,
                    BluetoothHidDeviceAppQosSettings.MAX);
            Executor executor = new Executor() {
                @Override
                public void execute(Runnable command) {
                    command.run();
                }
            };
            BluetoothHidDevice.Callback callback = new BluetoothHidDevice.Callback() {
                @Override
                public void onAppStatusChanged(BluetoothDevice pluggedDevice, boolean registered) {
                    super.onAppStatusChanged(pluggedDevice, registered);
                    if (registered) {
                        if (null != pluggedDevice){
                            //mBluetoothDeviceFound.add(pluggedDevice);
                            //mAdapter.add(pluggedDevice.getName());
                            Log.e(TAG, "onAppStatusChanged:" + pluggedDevice.getName());
                        }
                        List<BluetoothDevice> pairedDevices = mBluetoothHidDevice.getDevicesMatchingConnectionStates(new int[]{BluetoothProfile.STATE_CONNECTING, BluetoothProfile.STATE_CONNECTED, BluetoothProfile.STATE_DISCONNECTED, BluetoothProfile.STATE_DISCONNECTING});
                        if (!pairedDevices.isEmpty()) {
                            for (BluetoothDevice bluetoothDevice : pairedDevices) {
                                int status = mBluetoothHidDevice.getConnectionState(bluetoothDevice);
                                Log.e(TAG, "onAppStatusChanged:" + bluetoothDevice.getName() + " status:" + status);
//                                if (BluetoothProfile.STATE_DISCONNECTED == status) {
//                                    if (!mBluetoothHidDevice.connect(bluetoothDevice)) {
//                                        Log.e(TAG, "connect false");
//                                    } else {
//                                        Log.e(TAG, "connect:" + bluetoothDevice.getName());
//                                    }
//                                }
                            }
                        }
                    }
                }

                @Override
                public void onConnectionStateChanged(BluetoothDevice device, int state) {
                    super.onConnectionStateChanged(device, state);
                    if (state == BluetoothProfile.STATE_CONNECTED) {
                        mOtherDevice = device;
                    } else if (state == BluetoothProfile.STATE_CONNECTING) {
                        byte[] data = new byte[]{(byte) 63};
                        mBluetoothHidDevice.sendReport(device, 32, data);
                    }
                    String strStatus;
                    switch (state) {
                        case BluetoothProfile.STATE_DISCONNECTED:
                            strStatus = "STATE_DISCONNECTED";
                            mTip.setText("断开连接:" + device.getName());
                            break;
                        case BluetoothProfile.STATE_CONNECTING:
                            strStatus = "STATE_CONNECTING";
                            mTip.setText("连接中:" + device.getName());
                            break;
                        case BluetoothProfile.STATE_CONNECTED:
                            strStatus = "STATE_CONNECTED";
                            mTip.setText("连接成功:" + device.getName());
                            break;
                        case BluetoothProfile.STATE_DISCONNECTING:
                            strStatus = "STATE_DISCONNECTING";
                            mTip.setText("断开中:" + device.getName());
                            break;
                        default:
                            strStatus = "STATE_UNKNOWN";
                            break;
                    }
                    Log.e(TAG, "onConnectionStateChanged " + strStatus);
                }

                @Override
                public void onGetReport(BluetoothDevice device, byte type, byte id, int bufferSize) {
                    super.onGetReport(device, type, id, bufferSize);
                }

                @Override
                public void onSetReport(BluetoothDevice device, byte type, byte id, byte[] data) {
                    super.onSetReport(device, type, id, data);
                }

                @Override
                public void onSetProtocol(BluetoothDevice device, byte protocol) {
                    super.onSetProtocol(device, protocol);
                }

                @Override
                public void onInterruptData(BluetoothDevice device, byte reportId, byte[] data) {
                    super.onInterruptData(device, reportId, data);
                }

                @Override
                public void onVirtualCableUnplug(BluetoothDevice device) {
                    super.onVirtualCableUnplug(device);
                }
            };
            mBluetoothHidDevice.registerApp(spdRecord, null, qosOut, executor, callback);
            BluetoothHelper.setScanMode(mBluetoothAdapter, BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE, 300000);
        }
    }

    public void doServiceDisconnected(int profile) {
        Log.e(TAG, "onServiceDisconnected profile:" + profile);
    }

    @Override
    public void onPointerCaptureChanged(boolean hasCapture) {
        Log.e(TAG, "onPointerCaptureChanged hasCapture:" + hasCapture);
    }

    byte []MOUSE_KEYBOARD_COMBO = new byte[]{
            //MOUSE TLC
            0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)
            0x09, 0x02,                         // USAGE (Mouse)

            (byte)0xa1, 0x01,                         // COLLECTION (Application)
            0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)
            0x09, 0x02,                         // USAGE (Mouse)
            (byte)0xa1, 0x02,        //       COLLECTION (Logical)

            (byte)0x85, 0x04,               //   REPORT_ID (Mouse)
            0x09, 0x01,                         //   USAGE (Pointer)
            (byte)0xa1, 0x00,                         //   COLLECTION (Physical)
            0x05, 0x09,                         //     USAGE_PAGE (Button)
            0x19, 0x01,                         //     USAGE_MINIMUM (Button 1)
            0x29, 0x02,                         //     USAGE_MAXIMUM (Button 2)
            0x15, 0x00,                         //     LOGICAL_MINIMUM (0)
            0x25, 0x01,                         //     LOGICAL_MAXIMUM (1)
            0x75, 0x01,                         //     REPORT_SIZE (1)
            (byte)0x95, 0x02,                         //     REPORT_COUNT (2)
            (byte)0x81, 0x02,                         //     INPUT (Data,Var,Abs)
            (byte)0x95, 0x01,                         //     REPORT_COUNT (1)
            0x75, 0x06,                         //     REPORT_SIZE (6)
            (byte)0x81, 0x03,                         //     INPUT (Cnst,Var,Abs)
            0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop)
            0x09, 0x30,                         //     USAGE (X)
            0x09, 0x31,                         //     USAGE (Y)
            0x16, 0x01,(byte)0xf8,                         //     LOGICAL_MINIMUM (-2047)
            0x26, (byte)0xff,0x07,                         //     LOGICAL_MAXIMUM (2047)
            0x75, 0x10,                         //     REPORT_SIZE (16)
            (byte)0x95, 0x02,                         //     REPORT_COUNT (2)
            (byte)0x81, 0x06,                         //     INPUT (Data,Var,Rel)

            (byte)0xa1, 0x02,        //       COLLECTION (Logical)
            (byte)0x85, 0x06,               //   REPORT_ID (Feature)
            0x09, 0x48,        //         USAGE (Resolution Multiplier)

            0x15, 0x00,        //         LOGICAL_MINIMUM (0)
            0x25, 0x01,        //         LOGICAL_MAXIMUM (1)
            0x35, 0x01,        //         PHYSICAL_MINIMUM (1)
            0x45, 0x04,        //         PHYSICAL_MAXIMUM (4)
            0x75, 0x02,        //         REPORT_SIZE (2)
            (byte)0x95, 0x01,        //         REPORT_COUNT (1)

            (byte)0xb1, 0x02,        //         FEATURE (Data,Var,Abs)


            (byte)0x85, 0x04,               //   REPORT_ID (Mouse)
            //0x05, 0x01,                         //     USAGE_PAGE (Generic Desktop)
            0x09, 0x38,        //         USAGE (Wheel)

            0x15, (byte)0x81,        //         LOGICAL_MINIMUM (-127)
            0x25, 0x7f,        //         LOGICAL_MAXIMUM (127)
            0x35, 0x00,        //         PHYSICAL_MINIMUM (0)        - reset physical
            0x45, 0x00,        //         PHYSICAL_MAXIMUM (0)
            0x75, 0x08,        //         REPORT_SIZE (8)
            (byte)0x95, 0x01,                         //     REPORT_COUNT (1)
            (byte)0x81, 0x06,                         //     INPUT (Data,Var,Rel)
            (byte)0xc0,              //       END_COLLECTION

            (byte)0xa1, 0x02,        //       COLLECTION (Logical)
            (byte)0x85, 0x06,               //   REPORT_ID (Feature)
            0x09, 0x48,        //         USAGE (Resolution Multiplier)

            0x15, 0x00,        //         LOGICAL_MINIMUM (0)
            0x25, 0x01,        //         LOGICAL_MAXIMUM (1)
            0x35, 0x01,        //         PHYSICAL_MINIMUM (1)
            0x45, 0x04,        //         PHYSICAL_MAXIMUM (4)
            0x75, 0x02,        //         REPORT_SIZE (2)
            (byte)0x95, 0x01,        //         REPORT_COUNT (1)

            (byte)0xb1, 0x02,        //         FEATURE (Data,Var,Abs)

            0x35, 0x00,        //         PHYSICAL_MINIMUM (0)        - reset physical
            0x45, 0x00,        //         PHYSICAL_MAXIMUM (0)
            0x75, 0x04,        //         REPORT_SIZE (4)
            (byte)0xb1, 0x03,        //         FEATURE (Cnst,Var,Abs)



            (byte)0x85, 0x04,               //   REPORT_ID (Mouse)
            0x05, 0x0c,        //         USAGE_PAGE (Consumer Devices)
            0x0a, 0x38, 0x02,  //         USAGE (AC Pan)

            0x15, (byte)0x81,        //         LOGICAL_MINIMUM (-127)
            0x25, 0x7f,        //         LOGICAL_MAXIMUM (127)
            0x75, 0x08,        //         REPORT_SIZE (8)
            (byte)0x95, 0x01,        //         REPORT_COUNT (1)
            (byte)0x81, 0x06,        //         INPUT (Data,Var,Rel)
            (byte)0xc0,              //       END_COLLECTION
            (byte)0xc0,              //       END_COLLECTION

            (byte)0xc0,                               //   END_COLLECTION
            (byte)0xc0,                                //END_COLLECTION

            0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)

            0x09, 0x06,                         // Usage (Keyboard)
            (byte)0xA1, 0x01,                         // Collection (Application)
            (byte)0x85, 0x08,                           //   REPORT_ID (Keyboard)
            0x05, 0x07,                         //     Usage Page (Key Codes)
            0x19, (byte)0xe0,                         //     Usage Minimum (224)
            0x29, (byte)0xe7,                         //     Usage Maximum (231)
            0x15, 0x00,                         //     Logical Minimum (0)
            0x25, 0x01,                         //     Logical Maximum (1)
            0x75, 0x01,                         //     Report Size (1)
            (byte)0x95, 0x08,                         //     Report Count (8)
            (byte)0x81, 0x02,                         //     Input (Data, Variable, Absolute)

            (byte)0x95, 0x01,                         //     Report Count (1)
            0x75, 0x08,                         //     Report Size (8)
            (byte)0x81, 0x01,                         //     Input (Constant) reserved byte(1)



            (byte)0x95, 0x01,                         //     Report Count (1)
            0x75, 0x08,                         //     Report Size (8)
            0x15, 0x00,                         //     Logical Minimum (0)
            0x25, 0x65,                         //     Logical Maximum (101)
            0x05, 0x07,                         //     Usage Page (Key codes)
            0x19, 0x00,                         //     Usage Minimum (0)
            0x29, 0x65,                         //     Usage Maximum (101)
            (byte)0x81, 0x00,                         //     Input (Data, Array) Key array(6 bytes)
            (byte)0xc0                               // End Collection (Application)
    };
}