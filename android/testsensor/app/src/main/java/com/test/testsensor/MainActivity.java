package com.test.testsensor;

import androidx.appcompat.app.AppCompatActivity;

import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;

import java.util.List;

public class MainActivity extends AppCompatActivity implements MouseSensorLogic.IMouseSensorLogicCallback{
    private static final String TAG = "test";
    private MouseSensorLogic mMouseSensorLogic = null;
    private MyDrawView myDrawView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.btn_list).setOnClickListener(v->onGetList());
        findViewById(R.id.btn_register).setOnClickListener(v->onRegister());
        myDrawView = findViewById(R.id.drawView);
    }

    private void onGetList(){
        SensorManager sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        List<Sensor> sensors = sensorManager.getSensorList(Sensor.TYPE_ACCELEROMETER);
        String allText = "";
        for (Sensor sensor : sensors){
            String name = sensor.getName();
            int type = sensor.getType();
            allText += name + " " + type  + "\n";
        }
        Log.e(TAG, allText);
    }

    private void onRegister(){
        SensorManager sensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        mMouseSensorLogic = new MouseSensorLogic(sensorManager, this);
    }

    @Override
    public void onMouseMove(float offsetX, float offsetY) {
        float x = myDrawView.mX + offsetX;
        if (x < 0){
            x = 0;
        }
        if (x > myDrawView.mWidth){
            x = myDrawView.mWidth;
        }
        float y = myDrawView.mY + offsetY;
        if (y < 0){
            y = 0;
        }
        if (y > myDrawView.mHeight){
            y = myDrawView.mHeight;
        }
        myDrawView.mX = x;
        myDrawView.mY = y;
        myDrawView.postInvalidate();
    }

    @Override
    public void onEvent(int event) {

    }

}