package com.xixi.observeapp.activity;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.database.Observable;
import android.hardware.Camera;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.media.MediaMuxer;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Surface;
import android.view.WindowManager;
import android.widget.TextView;


import com.google.gson.Gson;
import com.xixi.observeapp.R;
import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.bean.ServiceRandomResult;
import com.xixi.observeapp.network.ApiManager;
import com.xixi.observeapp.network.Constants;
import com.xixi.observeapp.network.ObserveService;

import java.io.FileOutputStream;
import java.math.BigDecimal;
import java.nio.ByteBuffer;
import java.util.ArrayList;

import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;


public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private TextView mLog;

    public static class Test{
        public BigDecimal bigDecimal;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(this, new String[]{
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.INTERNET,
                Manifest.permission.ACCESS_NETWORK_STATE,
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.CAMERA,
                Manifest.permission.ACCESS_WIFI_STATE,
                Manifest.permission.READ_PHONE_STATE,
        }, 99);

        findViewById(R.id.btn_login).setOnClickListener(v -> {
            Intent intent = new Intent();
            intent.setClass(this, LoginActivify.class);
            startActivity(intent);
        });

        findViewById(R.id.btn_test).setOnClickListener(v->onTest());
    }

    private void onTest(){
        try{
            ObserveService observeService = ApiManager.getInstance().getProxy(ObserveService.class);
            observeService.getTestJson()
                    .subscribeOn(Schedulers.newThread())
                    .observeOn(AndroidSchedulers.mainThread())
                    .subscribe(new Observer<Result<ObserveService.TestJson>>(){
                        @Override
                        public void onSubscribe(Disposable d) {
                            Log.e(TAG, "onSubscribe");
                        }

                        @Override
                        public void onNext(Result<ObserveService.TestJson> value) {
                            Log.e(TAG, "onNext");
                            Log.e(TAG, "result:" + value.getData().text);
                        }

                        @Override
                        public void onError(Throwable e) {
                            Log.e(TAG, "onError");
                            e.printStackTrace();
                        }

                        @Override
                        public void onComplete() {
                            Log.e(TAG, "onComplete");
                        }
                    });
            observeService.getServiceRandom()
                    .subscribeOn(Schedulers.newThread())
                    .observeOn(AndroidSchedulers.mainThread())
                    .subscribe(new Observer<Result<ServiceRandomResult>>() {
                        @Override
                        public void onSubscribe(Disposable d) {

                        }

                        @Override
                        public void onNext(Result<ServiceRandomResult> value) {
                            Log.e(TAG, "onNext ServiceRandomResult" );
                            String json = new Gson().toJson(value);
                            Log.e(TAG, "onNext:" + json);
                        }

                        @Override
                        public void onError(Throwable e) {

                        }

                        @Override
                        public void onComplete() {

                        }
                    });
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}