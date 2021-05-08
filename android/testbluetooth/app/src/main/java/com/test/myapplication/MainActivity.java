package com.test.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothHidDevice;
import android.bluetooth.BluetoothHidDeviceAppQosSettings;
import android.bluetooth.BluetoothHidDeviceAppSdpSettings;
import android.bluetooth.BluetoothProfile;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.lang.reflect.Method;
import java.nio.ByteBuffer;
import java.util.List;
import java.util.Set;
import java.util.concurrent.Executor;
import java.util.concurrent.ThreadPoolExecutor;

public class MainActivity extends AppCompatActivity implements BluetoothProfile.ServiceListener{
    private static final String TAG = "tag";
    private View mViewMouse;
    private View mViewKeyboard;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION, Manifest.permission.BLUETOOTH, Manifest.permission.BLUETOOTH_ADMIN,
                Manifest.permission.WAKE_LOCK, Manifest.permission.FOREGROUND_SERVICE}, 0);

        findViewById(R.id.btn_test).setOnClickListener(v->onTest());
        findViewById(R.id.btn_mouse).setOnClickListener(v->showPage(0));
        findViewById(R.id.btn_keyboard).setOnClickListener(v->showPage(1));
        LinearLayout contarinerKeyboard = findViewById(R.id.container_keyboard);
        int count = contarinerKeyboard.getChildCount();
        for (int i = 0;i < count; i++){
            ViewGroup viewGroup = (ViewGroup)contarinerKeyboard.getChildAt(i);
            setKeyboardTouchListener(viewGroup);
        }
        mViewMouse = findViewById(R.id.container_mouse);
        mViewKeyboard = findViewById(R.id.container_keyboard);
        View viewMouseMove = findViewById(R.id.view_mouse_move);

        //mouse move
        MouseMoveListener.IMouseMoveCallback moveCallback = new MouseMoveListener.IMouseMoveCallback(){
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
        };
        MouseMoveListener mouseMoveListener = new MouseMoveListener(moveCallback);
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

        showPage(0);
    }

    BluetoothAdapter mBluetoothAdapter = null;
    BluetoothHidDevice mBluetoothHidDevice = null;
    BluetoothDevice mOtherDevice = null;

    private boolean setScanMode(int mode, long durationMillis){
        boolean success = false;
        try {
            Class clazz = mBluetoothAdapter.getClass();
            Method method = clazz.getMethod("setScanMode", int.class, int.class);
            Object object = method.invoke(mBluetoothAdapter, mode, (int)durationMillis);
            if (object instanceof Boolean){
                success = (Boolean)object;
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return success;
    }
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

    private void onTest(){
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        int profile = BluetoothProfile.HID_DEVICE;
        //int profile = BluetoothProfile.HEADSET;
        boolean result = mBluetoothAdapter.getProfileProxy(this, this, profile);
        Log.e(TAG, "onTest :" + result);
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



    private void showPage(int page){
        mViewMouse.setVisibility(0 == page ? View.VISIBLE : View.GONE);
        mViewKeyboard.setVisibility(0 == page ? View.GONE : View.VISIBLE);
    }

    @Override
    public void onServiceConnected(int profile, BluetoothProfile proxy) {
        Log.e(TAG, "onServiceConnected profile:" + profile);
        if (proxy instanceof BluetoothHidDevice){
            mBluetoothHidDevice = (BluetoothHidDevice)proxy;
            BluetoothHidDeviceAppSdpSettings spdRecord = new BluetoothHidDeviceAppSdpSettings("Pixel HID1", "Mobile BController", "test",
                    BluetoothHidDevice.SUBCLASS1_COMBO,
                    MOUSE_KEYBOARD_COMBO);
            BluetoothHidDeviceAppQosSettings qosOut = new BluetoothHidDeviceAppQosSettings(BluetoothHidDeviceAppQosSettings.SERVICE_BEST_EFFORT,
                    800,
                    9,
                    0,
                    11250,
                    BluetoothHidDeviceAppQosSettings.MAX);
            Executor executor = new Executor(){
                @Override
                public void execute(Runnable command) {
                    command.run();
                }
            };
            BluetoothHidDevice.Callback callback = new BluetoothHidDevice.Callback(){
                @Override
                public void onAppStatusChanged(BluetoothDevice pluggedDevice, boolean registered) {
                    super.onAppStatusChanged(pluggedDevice, registered);
                    if (registered){
                        List<BluetoothDevice> pairedDevices = mBluetoothHidDevice.getDevicesMatchingConnectionStates(new int []{BluetoothProfile.STATE_CONNECTING,BluetoothProfile.STATE_CONNECTED,BluetoothProfile.STATE_DISCONNECTED,BluetoothProfile.STATE_DISCONNECTING});
                        mOtherDevice = pluggedDevice;

                        if (false&&null != mOtherDevice && mBluetoothHidDevice.getConnectionState(mOtherDevice) == BluetoothProfile.STATE_DISCONNECTED){
                            mBluetoothHidDevice.connect(mOtherDevice);
                            Log.e(TAG, "connect:" + mOtherDevice.getName());
                        }else{
                            Set<BluetoothDevice> bluetoothDeviceSet = mBluetoothAdapter.getBondedDevices();
                            if (!bluetoothDeviceSet.isEmpty()){
                                for (BluetoothDevice bluetoothDevice : bluetoothDeviceSet){
                                    if ("chenyue".equals(bluetoothDevice.getName())){
                                        int status = mBluetoothHidDevice.getConnectionState(bluetoothDevice);
                                        Log.e(TAG, "status:" + status);
                                        if (BluetoothProfile.STATE_DISCONNECTED == status){
                                            if (!mBluetoothHidDevice.connect(bluetoothDevice)){
                                                Log.e(TAG, "connect false");
                                            }else{
                                                Log.e(TAG, "connect:" + bluetoothDevice.getName());
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                @Override
                public void onConnectionStateChanged(BluetoothDevice device, int state) {
                    super.onConnectionStateChanged(device, state);
                    if (state == BluetoothProfile.STATE_CONNECTED){
                        mOtherDevice = device;
                    }else if (state == BluetoothProfile.STATE_CONNECTING){
                        byte []data = new byte[]{(byte)63};
                        mBluetoothHidDevice.sendReport(device, 32, data);
                    }
                    String strStatus;
                    switch (state){
                        case BluetoothProfile.STATE_DISCONNECTED:
                            strStatus = "STATE_DISCONNECTED";
                            break;
                        case BluetoothProfile.STATE_CONNECTING:
                            strStatus = "STATE_CONNECTING";
                            break;
                        case BluetoothProfile.STATE_CONNECTED:
                            strStatus = "STATE_CONNECTED";
                            break;
                        case BluetoothProfile.STATE_DISCONNECTING:
                            strStatus = "STATE_DISCONNECTING";
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
            setScanMode(BluetoothAdapter.SCAN_MODE_CONNECTABLE_DISCOVERABLE, 300000);
        }
    }

    @Override
    public void onServiceDisconnected(int profile) {
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