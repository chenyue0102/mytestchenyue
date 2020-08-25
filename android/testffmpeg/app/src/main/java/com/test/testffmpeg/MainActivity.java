package com.test.testffmpeg;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        findViewById(R.id.btn_open_file).setOnClickListener(v->onOpenFile());
        findViewById(R.id.btn_close_file).setOnClickListener(v->onCloseFile());
        findViewById(R.id.btn_pause_play).setOnClickListener(v->onPausePlay());
        findViewById(R.id.btn_resume_play).setOnClickListener(v->onResumePlay());
        findViewById(R.id.btn_seek).setOnClickListener(v->onSeek());

        String []permissions = new String[]{
                Manifest.permission.INTERNET,
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.CAMERA,
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.ACCESS_NETWORK_STATE,
                Manifest.permission.READ_PHONE_STATE,
        };
        String []requestPermissons = PermissionHelper.getNotGrantedPermissions(this, permissions);
        if (null != requestPermissons){
            ActivityCompat.requestPermissions(this, requestPermissons, 1);
        }
        init();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void init();

    private void onOpenFile(){
        String filePath = StorageHelper.getSDCardPath();
        filePath += "/v1080.mp4";
        openFile(filePath);
    }

    public native void openFile(String filePath);

    public void onPausePlay(){
        pausePlay();
    }

    private native void pausePlay();

    public void onResumePlay(){
        resumePlay();
    }

    private native void resumePlay();

    public void onSeek(){
        seek();
    }

    private native void seek();

    private void onCloseFile(){
        closeFile();
    }

    public native void closeFile();
}
