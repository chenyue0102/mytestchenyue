package com.test.testunity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;

import com.unity3d.player.UnityPlayerActivity;

import java.io.FileReader;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_start_game).setOnClickListener(v->startGame());
    }

    private void startGame(){
        try{
            FileReader file = new FileReader("/storage/emulated/0/AssetScene.unity3d");
            char c[] = new char[4];
            file.read(c);
            file.close();
        }catch(Exception e){
            e.printStackTrace();
        }
        Intent intent = new Intent(this, MyUnityPlayerActivity.class);
        startActivity(intent);
    }
}