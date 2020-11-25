package com.chenyue.reverb;


import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TableLayout;

import com.lamerman.FileDialog;
import com.lamerman.SelectionMode;

import tv.danmaku.ijk.media.example.widget.media.IjkVideoView;
import tv.danmaku.ijk.media.player.IjkMediaPlayer;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "reverb";
    private IjkVideoView mVideoView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_open).setOnClickListener(v->onOpen());

        IjkMediaPlayer.loadLibrariesOnce(null);
        IjkMediaPlayer.native_profileBegin("libijkplayer.so");

        String []permissions = new String[]{
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
        };
        String []requestPermissons = PermissionHelper.getNotGrantedPermissions(this, permissions);
        if (null != requestPermissons){
            ActivityCompat.requestPermissions(this, requestPermissons, 1);
        }

        TableLayout mHudView = (TableLayout) findViewById(R.id.hud_view);
        mVideoView = (IjkVideoView)findViewById(R.id.video_view);
        mVideoView.setHudView(mHudView);
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
                mVideoView.setVideoPath(filePath);
                mVideoView.start();
            }
        }
    }

    @Override
    protected void onDestroy(){
        super.onDestroy();
        IjkMediaPlayer.native_profileEnd();
    }
}