package com.example.testmedia;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.Button;

import java.io.File;

public class MainActivity extends AppCompatActivity {
    private TestMedia testMedia = new TestMedia();
    private String mediaFile;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        boolean sdCardExist = false;
        String sdDir = Environment.getExternalStorageDirectory().getAbsolutePath();
        mediaFile = sdDir + "/test.mp3";
        Log.i("tag", mediaFile);

        Button btnOpen = findViewById(R.id.btn_open_mp3);
        btnOpen.setOnClickListener((v)->playMp3File(mediaFile));
//        File  file = new File(mediaFile);
//        Log.i("tag", "file.exists()" + file.exists());
    }

    private void playMp3File(String mediaFile){
        testMedia.playMp3File(mediaFile);
    }
}
