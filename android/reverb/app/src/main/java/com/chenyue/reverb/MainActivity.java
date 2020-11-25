package com.chenyue.reverb;


import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

import com.lamerman.FileDialog;
import com.lamerman.SelectionMode;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "reverb";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_open).setOnClickListener(v->onOpen());


        String []permissions = new String[]{
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
        };
        String []requestPermissons = PermissionHelper.getNotGrantedPermissions(this, permissions);
        if (null != requestPermissons){
            ActivityCompat.requestPermissions(this, requestPermissons, 1);
        }
    }

    private static final int REQUEST_OPEN = 9999;
    private void onOpen(){
        Intent intent = new Intent(getBaseContext(), FileDialog.class); intent.putExtra(FileDialog.START_PATH, "/sdcard");

        //can user select directories or not
        intent.putExtra(FileDialog.CAN_SELECT_DIR, false);

        //alternatively you can set file filter
        intent.putExtra(FileDialog.FORMAT_FILTER, new String[] { "mp3" });

        intent.putExtra(FileDialog.SELECTION_MODE, SelectionMode.MODE_OPEN);

        startActivityForResult(intent, REQUEST_OPEN);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == Activity.RESULT_OK) {
            if (requestCode == REQUEST_OPEN){
                String filePath = data.getStringExtra(FileDialog.RESULT_PATH);
                Log.i(TAG, filePath);
            }
        }
    }
}