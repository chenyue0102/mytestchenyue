package com.test.testunity;

import android.os.Environment;

import java.io.File;

public class StorageHelper {
    public static String getSDCardPath(){
        if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
            File sdDir = Environment.getExternalStorageDirectory();
            return sdDir.getAbsolutePath();
        }else{
            return null;
        }
    }
}
