package com.test.myapplication;

import android.view.KeyEvent;

import java.util.HashMap;

public class KeyboardReport {
    public static final int ID = 8;

    public boolean leftControl = false;
    public boolean leftShift = false;
    public boolean leftAlt = false;
    public boolean leftGui = false;

    public boolean rightControl = false;
    public boolean rightShift = false;
    public boolean rightAlt = false;
    public boolean rightGui = false;
    public int key1 = KeyEvent.KEYCODE_UNKNOWN;

    private byte[]bytes = new byte[3];

    public KeyboardReport(){

    }

    public static boolean isCtrlKey(int keycode){
        boolean isCtrl = false;
        switch (keycode){
            case KeyEvent.KEYCODE_CTRL_LEFT:
            case KeyEvent.KEYCODE_CTRL_RIGHT:
            case KeyEvent.KEYCODE_SHIFT_LEFT:
            case KeyEvent.KEYCODE_SHIFT_RIGHT:
            case KeyEvent.KEYCODE_ALT_LEFT:
            case KeyEvent.KEYCODE_ALT_RIGHT:
                //case KeyEvent.KEYCODE_WINDOW:
                //case KeyEvent.KEYCODE_MENU:
                isCtrl = true;
                break;
            default:
                break;
        }
        return isCtrl;
    }

    public static byte setBit(byte old, int shiftOffset, boolean isSet){
        if (shiftOffset >= 0 && shiftOffset <= 7){
            byte b = 0b00000001;
            b = (byte)(b << shiftOffset);
            byte newValue = isSet ? (byte)(old | b) : (byte)(old & (~b));
            return newValue;
        }else{
            return 0;
        }
    }

    public void setCtrlKey(int keycode, boolean isClicked){
        switch (keycode){
            case KeyEvent.KEYCODE_CTRL_LEFT:
                leftControl = isClicked;
                break;
            case KeyEvent.KEYCODE_CTRL_RIGHT:
                rightControl = isClicked;
                break;
            case KeyEvent.KEYCODE_SHIFT_LEFT:
                leftShift = isClicked;
                break;
            case KeyEvent.KEYCODE_SHIFT_RIGHT:
                rightShift = isClicked;
                break;
            case KeyEvent.KEYCODE_ALT_LEFT:
                leftAlt = isClicked;
                break;
            case KeyEvent.KEYCODE_ALT_RIGHT:
                rightAlt = isClicked;
                break;
            default:
                break;
        }
    }

    public byte[] packByte(){
        bytes[0] = setBit(bytes[0], 0, leftControl);
        bytes[0] = setBit(bytes[0], 1, leftShift);
        bytes[0] = setBit(bytes[0], 2, leftAlt);
        bytes[0] = setBit(bytes[0], 3, leftGui);
        bytes[0] = setBit(bytes[0], 4, rightControl);
        bytes[0] = setBit(bytes[0], 5, rightShift);
        bytes[0] = setBit(bytes[0], 6, rightAlt);
        bytes[0] = setBit(bytes[0], 7, rightGui);
        if (KeyEventMap.containsKey(key1)){
            bytes[2] = (byte) (int) KeyEventMap.get(key1);
        }else{
            bytes[2] = 0;
        }
        return bytes;
    }

    public void reset(){
        leftControl = false;
        leftShift = false;
        leftAlt = false;
        leftGui = false;

        rightControl = false;
        rightShift = false;
        rightAlt = false;
        rightGui = false;
        key1 = KeyEvent.KEYCODE_UNKNOWN;
    }

    private HashMap<Integer, Integer> KeyEventMap = new HashMap<Integer, Integer>() {{
        put(KeyEvent.KEYCODE_UNKNOWN, 0);
        put(KeyEvent.KEYCODE_A, 4);
        put(KeyEvent.KEYCODE_B, 5);
        put(KeyEvent.KEYCODE_C, 6);
        put(KeyEvent.KEYCODE_D, 7);
        put(KeyEvent.KEYCODE_E, 8);
        put(KeyEvent.KEYCODE_F, 9);
        put(KeyEvent.KEYCODE_G, 10);
        put(KeyEvent.KEYCODE_H, 11);
        put(KeyEvent.KEYCODE_I, 12);
        put(KeyEvent.KEYCODE_J, 13);
        put(KeyEvent.KEYCODE_K, 14);
        put(KeyEvent.KEYCODE_L, 15);
        put(KeyEvent.KEYCODE_M, 16);
        put(KeyEvent.KEYCODE_N, 17);
        put(KeyEvent.KEYCODE_O, 18);
        put(KeyEvent.KEYCODE_P, 19);
        put(KeyEvent.KEYCODE_Q, 20);
        put(KeyEvent.KEYCODE_R, 21);
        put(KeyEvent.KEYCODE_S, 22);
        put(KeyEvent.KEYCODE_T, 23);
        put(KeyEvent.KEYCODE_U, 24);
        put(KeyEvent.KEYCODE_V, 25);
        put(KeyEvent.KEYCODE_W, 26);
        put(KeyEvent.KEYCODE_X, 27);
        put(KeyEvent.KEYCODE_Y, 28);
        put(KeyEvent.KEYCODE_Z, 29);


        put(KeyEvent.KEYCODE_1, 30);
        put(KeyEvent.KEYCODE_2, 31);
        put(KeyEvent.KEYCODE_3, 32);
        put(KeyEvent.KEYCODE_4, 33);
        put(KeyEvent.KEYCODE_5, 34);
        put(KeyEvent.KEYCODE_6, 35);
        put(KeyEvent.KEYCODE_7, 36);
        put(KeyEvent.KEYCODE_8, 37);
        put(KeyEvent.KEYCODE_9, 38);
        put(KeyEvent.KEYCODE_0, 39);

        put(KeyEvent.KEYCODE_F1, 58);
        put(KeyEvent.KEYCODE_F2, 59);
        put(KeyEvent.KEYCODE_F3, 60);
        put(KeyEvent.KEYCODE_F4, 61);
        put(KeyEvent.KEYCODE_F5, 62);
        put(KeyEvent.KEYCODE_F6, 63);
        put(KeyEvent.KEYCODE_F7, 64);
        put(KeyEvent.KEYCODE_F8, 65);
        put(KeyEvent.KEYCODE_F9, 66);
        put(KeyEvent.KEYCODE_F10, 67);
        put(KeyEvent.KEYCODE_F11, 68);
        put(KeyEvent.KEYCODE_F12, 69);

        put(KeyEvent.KEYCODE_ENTER, 40);
        put(KeyEvent.KEYCODE_ESCAPE, 41);
        put(KeyEvent.KEYCODE_DEL, 42);
        put(KeyEvent.KEYCODE_TAB, 43);
        put(KeyEvent.KEYCODE_SPACE, 44);
        put(KeyEvent.KEYCODE_MINUS, 45);
        put(KeyEvent.KEYCODE_EQUALS, 46);
        put(KeyEvent.KEYCODE_LEFT_BRACKET, 47);
        put(KeyEvent.KEYCODE_RIGHT_BRACKET, 48);
        put(KeyEvent.KEYCODE_BACKSLASH, 49);
        put(KeyEvent.KEYCODE_SEMICOLON, 51);
        put(KeyEvent.KEYCODE_APOSTROPHE, 52);
        put(KeyEvent.KEYCODE_GRAVE, 53);
        put(KeyEvent.KEYCODE_COMMA, 54);
        put(KeyEvent.KEYCODE_PERIOD, 55);
        put(KeyEvent.KEYCODE_SLASH, 56);

        put(KeyEvent.KEYCODE_SCROLL_LOCK, 71);
        put(KeyEvent.KEYCODE_INSERT, 73);
        put(KeyEvent.KEYCODE_HOME, 74);
        put(KeyEvent.KEYCODE_PAGE_UP, 75);
        put(KeyEvent.KEYCODE_FORWARD_DEL, 76);
        put(KeyEvent.KEYCODE_MOVE_END, 77);
        put(KeyEvent.KEYCODE_PAGE_DOWN, 78);
        put(KeyEvent.KEYCODE_NUM_LOCK, 83);

        put(KeyEvent.KEYCODE_DPAD_RIGHT, 79);
        put(KeyEvent.KEYCODE_DPAD_LEFT, 80);
        put(KeyEvent.KEYCODE_DPAD_DOWN, 81);
        put(KeyEvent.KEYCODE_DPAD_UP, 82);

        put(KeyEvent.KEYCODE_AT, 31);
        put(KeyEvent.KEYCODE_POUND, 32);
        put(KeyEvent.KEYCODE_STAR, 37);
    }};
}
