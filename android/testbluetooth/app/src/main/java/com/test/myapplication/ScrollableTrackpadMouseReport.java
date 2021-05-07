package com.test.myapplication;

import java.nio.ByteBuffer;

public class ScrollableTrackpadMouseReport {
    public static final int ID = 4;
    public boolean leftButton;
    public boolean rightButton;
    public byte dxLsb;
    public byte dxMsb;
    public byte dyLsb;
    public byte dyMsb;
    public byte vScroll;
    public byte hScroll;
    private byte []bytes = new byte[7];

    public ScrollableTrackpadMouseReport(){

    }

    public byte[] packByte(){
        if (leftButton){
            bytes[0] = (byte)(bytes[0] | 0b1);
        }else{
            bytes[0] = (byte)(bytes[0] & 0b110);
        }
        if (rightButton){
            bytes[0] = (byte)(bytes[0] | 0b10);
        }else{
            bytes[0] = (byte)(bytes[0] & 0b101);
        }
        bytes[1] = dxLsb;
        bytes[2] = dxMsb;

        bytes[3] = dyLsb;
        bytes[4] = dyMsb;

        bytes[5] = vScroll;
        bytes[6] = hScroll;
        return bytes;
    }
}
