package com.test.testsensor;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;


public class MouseSensorLogic {
    private static final String TAG = "sensor";
    private static final int SAMPLING_PERIOD_US = SensorManager.SENSOR_DELAY_GAME;
    private static final float MIN_ACC_VALUE = 0.5f;
    private static final float MAX_ACC_VALUE = 8.5f;
    private static final float MIN_GYRO_VALUE = 0.1f;

    private static final float MAX_MOVE_VALUE = 20;

    interface IMouseSensorLogicCallback{
        int EVENT_CLICK = 1;
        void onMouseMove(float offsetX, float offsetY);
        void onEvent(int event);
    }

    private SensorManager mSensorManager;
    private SensorEventListener mSensorEventListenerAccelerometer;//加速度传感器
    private SensorEventListener mSensorEventListenerGyroscope;//陀螺仪传感器
    private IMouseSensorLogicCallback mCallback;
    private long mTimestampAcc = 0;


    public MouseSensorLogic(SensorManager sensorManager, IMouseSensorLogicCallback callback){
        mSensorManager = sensorManager;
        mCallback = callback;
        init();
        /*
        gravity[0] = alpha * gravity[0] + (1 - alpha) * event.values[0];
        gravity[1] = alpha * gravity[1] + (1 - alpha) * event.values[1];
        gravity[2] = alpha * gravity[2] + (1 - alpha) * event.values[2];

        linear_acceleration[0] = event.values[0] - gravity[0];
        linear_acceleration[1] = event.values[1] - gravity[1];
        linear_acceleration[2] = event.values[2] - gravity[2];
        */
    }

    private float mGravity[] = new float[3];
    private float mGravityAlpha = 0.8f;
    private float[] removeGravity(float values[]){
        float linear_acceleration[] = new float[3];
        mGravity[0] = mGravityAlpha * mGravity[0] + (1 - mGravityAlpha) * values[0];
        mGravity[1] = mGravityAlpha * mGravity[1] + (1 - mGravityAlpha) * values[1];
        mGravity[2] = mGravityAlpha * mGravity[2] + (1 - mGravityAlpha) * values[2];

        linear_acceleration[0] = values[0] - mGravity[0];
        linear_acceleration[1] = values[1] - mGravity[1];
        linear_acceleration[2] = values[2] - mGravity[2];
        return linear_acceleration;
    }

    //归一化
    private float[] normalize(float values[]){
        float []n = new float[3];
        double length = (double) values[0] * values[0] + (double)values[1] * values[1] + (double)values[2] * values[2];
        length = Math.sqrt(length);
        n[0] = (float)(values[0] / length);
        n[1] = (float)(values[1] / length);
        n[2] = (float)(values[2] / length);
        return n;
    }

    private float[] vectorToEulerAngles(float xyz[]){
        double x = xyz[0];
        double y = xyz[1];
        double z = xyz[2];
        float [] eulerAngles = new float[3];
        if (0 != x && 0 != y && 0 != z){
            double d = (x * x + z * z) / (x *x + y * y + z * z);
            d = Math.sqrt(d);
            d = Math.acos(d);
            d = Math.toDegrees(d);
            eulerAngles[0] = (float)d;
            if (y > 0){
                eulerAngles[0] = 360 - eulerAngles[0];
            }

            eulerAngles[1] = (float) Math.toDegrees(Math.atan2(x, z));
            if (eulerAngles[1] < 0){
                eulerAngles[1] += 180;
            }
            if (x < 0){
                eulerAngles[1] += 180;
            }
            eulerAngles[2] = 0;
        }
        return eulerAngles;
    }

    //加速度传感器
    private void onSensorChangedAccelerometer(SensorEvent event){
        //float values[] = removeGravity(event.values);
        float values[] = normalize(event.values);
        float radianX = values[0];//加速传感器 米/秒2
        float radianY = values[1];
        float radianZ = values[2];
//        radianX = calcMove(radianX);
//        radianY = calcMove(radianY);
//        radianZ = calcMove(radianZ);
        if (radianX > MIN_ACC_VALUE || radianY > MIN_ACC_VALUE || radianZ > MIN_ACC_VALUE){
            Log.e(TAG, "Acce " + " radianX:" + radianX + " radianY：" + radianY + " radianZ:" + radianZ);
        }
//        if (0.0f == radianX && 0.0f == radianY){
//            mTimestampAcc = 0;
//            return;
//        }
//        if (null == mCallback){
//            return;
//        }
//        mCallback.onMouseMove(getMove(radianX), getMove(-radianY));
    }

    private float getMove(float value){
        float percent = value / MAX_ACC_VALUE;
        return (percent * MAX_MOVE_VALUE);
    }

    private float calcMove(float value){
        if (Math.abs(value) < MIN_ACC_VALUE){
            value = 0.0f;
        }else if (value > MAX_ACC_VALUE){
            value = MAX_ACC_VALUE;
        }else if (value < -MAX_ACC_VALUE){
            value = -MAX_ACC_VALUE;
        }
        return value;
    }

    private float calcGyroscope(float value){
        if (Math.abs(value) < MIN_GYRO_VALUE){
            value = 0.0f;
        }
        return value;
    }

    private void onSensorChangedGyroscope(SensorEvent event){
        float radianX = calcGyroscope(event.values[0]);//加速传感器 米/秒2
        float radianY = calcGyroscope(event.values[1]);
        float radianZ = calcGyroscope(event.values[2]);

        boolean isPrint = false;
        if (radianX != 0.0f || radianY != 0.0f || radianZ != 0.0f){
            //Log.e(TAG, "Gyroscope:" + " radianX:" + radianX + " radianY：" + radianY + " radianZ:" + radianZ);
        }

    }

    private void init(){
        if (null == mSensorManager){
            return;
        }
        mSensorEventListenerAccelerometer = new SensorEventListener(){
            @Override
            public void onSensorChanged(SensorEvent event) {
                if (null != event.sensor
                        && Sensor.TYPE_ACCELEROMETER == event.sensor.getType()
                        && event.values.length == 3) {
                    onSensorChangedAccelerometer(event);
                }
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) {

            }
        };

        mSensorEventListenerGyroscope = new SensorEventListener() {
            @Override
            public void onSensorChanged(SensorEvent event) {
                if (null != event.sensor
                        && Sensor.TYPE_GYROSCOPE == event.sensor.getType()
                        && event.values.length == 3) {
                    onSensorChangedGyroscope(event);
                }
            }

            @Override
            public void onAccuracyChanged(Sensor sensor, int accuracy) {

            }
        };
        Sensor sensorAccelerometer = mSensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);//TYPE_GYROSCOPE
        mSensorManager.registerListener(mSensorEventListenerAccelerometer, sensorAccelerometer, SAMPLING_PERIOD_US);

        Sensor sensorGyroscope = mSensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        mSensorManager.registerListener(mSensorEventListenerGyroscope, sensorGyroscope, SAMPLING_PERIOD_US);
    }
}
