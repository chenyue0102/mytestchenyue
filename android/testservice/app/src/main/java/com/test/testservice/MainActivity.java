package com.test.testservice;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Messenger;
import android.util.Log;
import android.widget.Button;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "mytest";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btnStart = findViewById(R.id.btn_start);
        btnStart.setOnClickListener(view->doStartService());

        Button btnStop = findViewById(R.id.btn_stop);
        btnStop.setOnClickListener(view->doStopService());

        Button btnBind = findViewById(R.id.btn_bind);
        btnBind.setOnClickListener(view->doBind());

        Button btnUnbind = findViewById(R.id.btn_unbind);
        btnUnbind.setOnClickListener(view->doUnbind());
    }

    void doStartService(){
        Log.i(TAG, "MainActivity doStartService");
        Intent intent = new Intent(this, MyService.class);
        intent.putExtra("test", 1);
        startService(intent);
    }

    void doStopService(){
        Log.i(TAG, "MainActivity doStopService");
        Intent intent = new Intent(this, MyService.class);
        stopService(intent);
    }

    ArrayList<ServiceConnection> serviceConnections = new ArrayList<>();
    void doBind(){
        Log.i(TAG, "MainActivity doBind");
        ServiceConnection serviceConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                serviceConnections.add(this);
                Log.i(TAG, "MainActivity onServiceConnected");
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {
                Log.i(TAG, "MainActivity onServiceDisconnected");
            }
        };

        Intent intent = new Intent(this, MyService.class);
        bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE);
    }

    void doUnbind(){
        if (!serviceConnections.isEmpty()){
            Log.i(TAG, "MainActivity doUnbind");
            ServiceConnection serviceConnection = serviceConnections.remove(serviceConnections.size() - 1);
            unbindService(serviceConnection);
        }
    }
}
