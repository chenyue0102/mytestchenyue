package com.test.testffmpeg;

import android.content.Context;
import android.content.pm.PackageManager;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;

import java.util.LinkedList;
import java.util.List;

public class PermissionHelper {
    public static boolean isAllPermissionGranted(@NonNull Context context, @NonNull String ...permissions){
        for (int i = 0; i < permissions.length; i++){
            if (ActivityCompat.checkSelfPermission(context, permissions[i]) != PackageManager.PERMISSION_GRANTED){
                return false;
            }
        }
        return true;
    }

    public static boolean isAllPermissionGranted(@NonNull int []grantResults){
        for (int i = 0; i < grantResults.length; i++){
            if (grantResults[i] != PackageManager.PERMISSION_GRANTED){
                return false;
            }
        }
        return true;
    }

    public static String[] getNotGrantedPermissions(@NonNull Context context, @NonNull String ...permissions){
        List<String> list = new LinkedList<>();
        for (int i = 0; i < permissions.length; i++){
            if (ActivityCompat.checkSelfPermission(context, permissions[i]) != PackageManager.PERMISSION_GRANTED){
                list.add(permissions[i]);
            }
        }
        if (list.isEmpty()){
            return null;
        }else{
            return list.toArray(new String[list.size()]);
        }
    }
}
