package com.example.testrk3328;

import androidx.appcompat.app.AppCompatActivity;

import android.app.DemoManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.app.IDemoManager;

public class MainActivity extends AppCompatActivity {
    /**
     * demo service
     */
    public static final String DEMO_SERVICE = "demo";
    public static final String TAG = "test";
    private TextView mText;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.btn_test).setOnClickListener(v->onTest());
        mText = findViewById(R.id.tv_text);
    }

    IDemoManager mDemoManager = null;
    private void onTest(){
        DemoManager demoManager = (DemoManager)getSystemService(DEMO_SERVICE);
        int sum = demoManager.sum(101,202);
        myLog("demoManager.sum:" + sum);
        String str = demoManager.getText("abc");
        myLog(str + " uithread:" + Thread.currentThread().getName());
    }

    private void myLog(String str){
        Log.e(TAG, str);
        mText.append(str + "\n");
        Thread.currentThread().getId();
    }
}