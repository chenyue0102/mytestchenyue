package com.xixi.observeapp.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.EditText;

import com.xixi.observeapp.R;

public class LoginActivify extends AppCompatActivity {
    EditText mServerAddress;
    EditText mLoginName;
    EditText mPassword;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_activify);

        mServerAddress = findViewById(R.id.et_server_address);
        mLoginName = findViewById(R.id.et_login_name);
        mPassword = findViewById(R.id.et_password);
        findViewById(R.id.btn_close).setOnClickListener(v->this.onBackPressed());
    }
}