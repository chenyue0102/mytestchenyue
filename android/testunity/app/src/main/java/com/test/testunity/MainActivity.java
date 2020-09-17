package com.test.testunity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import com.unity3d.player.UnityPlayerActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_start_game).setOnClickListener(v->startGame());
    }

    private void startGame(){
        Intent intent = new Intent(this, MyUnityPlayerActivity.class);
        startActivity(intent);
    }
}