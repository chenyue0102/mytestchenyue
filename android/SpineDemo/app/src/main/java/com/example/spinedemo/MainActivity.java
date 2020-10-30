package com.example.spinedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;



public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("spinewrap");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_load).setOnClickListener(v->onLoad());


    }

    private void onLoad(){
        Intent intent = new Intent(this, SpineActivity.class);
        startActivity(intent);
    }
}
