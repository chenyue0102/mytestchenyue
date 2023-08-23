package com.xixi.observeapp.activity;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PixelFormat;
import android.hardware.display.DisplayManager;
import android.hardware.display.VirtualDisplay;
import android.media.Image;
import android.media.ImageReader;
import android.media.projection.MediaProjection;
import android.media.projection.MediaProjectionManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.util.Base64;
import android.util.DisplayMetrics;

import com.xixi.observeapp.R;
import com.xixi.observeapp.constants.Constants;
import com.xixi.observeapp.service.WebSocketService;
import com.xixi.observeapp.util.SpUtils;

import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;

public class ScreenShotActivity extends AppCompatActivity {
    private static final int REQUEST_CODE = 1000;
    MediaProjectionManager mediaProjectionManager;
    WebSocketService.MyBinder myBinder;
    ServiceConnection serviceConnection;
    VirtualDisplay virtualDisplay;
    ImageReader imageReader;
    MediaProjection mediaProjection;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_screen_shot);
        mediaProjectionManager = (MediaProjectionManager)getSystemService(Context.MEDIA_PROJECTION_SERVICE);
        new Handler().postDelayed(()->startScreenCapture(), 500);

        serviceConnection = new ServiceConnection() {
            @Override
            public void onServiceConnected(ComponentName name, IBinder service) {
                myBinder = (WebSocketService.MyBinder)service;
            }

            @Override
            public void onServiceDisconnected(ComponentName name) {
                myBinder = null;
            }
        };
        Intent intent = new Intent(this, WebSocketService.class);
        bindService(intent, serviceConnection, Context.BIND_AUTO_CREATE);
    }

    private void startScreenCapture(){
        startActivityForResult(mediaProjectionManager.createScreenCaptureIntent(), REQUEST_CODE);
    }

    @SuppressLint("WrongConstant")
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data){
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE){
            if (null == myBinder){
                return;
            }
            if (resultCode != RESULT_OK){
                setResultImage(null);
            }else{
                mediaProjection = mediaProjectionManager.getMediaProjection(resultCode, data);
                DisplayMetrics metrics = new DisplayMetrics();
                getWindowManager().getDefaultDisplay().getMetrics(metrics);

                imageReader = ImageReader.newInstance(metrics.widthPixels, metrics.heightPixels, PixelFormat.RGBA_8888, 1);
                virtualDisplay = mediaProjection.createVirtualDisplay("screencapture", metrics.widthPixels, metrics.heightPixels,
                        metrics.densityDpi, DisplayManager.VIRTUAL_DISPLAY_FLAG_AUTO_MIRROR, imageReader.getSurface(), null, null);

                new Handler().postDelayed(()->doCapture(), 1000);
                onBackPressed();
            }
        }
    }

    private void doCapture(){
        Image image = imageReader.acquireLatestImage();
        setResultImage(image);
        if (null != virtualDisplay){
            virtualDisplay.release();
            virtualDisplay = null;
        }
    }

    private void setResultImage(Image image){
        if (null != myBinder){
            String text = null;
            int width = 0, height = 0;
            if (null != image){
                ByteBuffer buffer = image.getPlanes()[0].getBuffer();
                byte[] bytes = new byte[buffer.remaining()];
                buffer.get(bytes);
                Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length, null);
                ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
                bitmap.compress(Bitmap.CompressFormat.PNG, 100, outputStream);
                byte []data = outputStream.toByteArray();
                text = new String(Base64.encode(data, Base64.DEFAULT));
                text = "data:image/png;base64," + text;
                width = image.getWidth();
                height = image.getHeight();
            }
            myBinder.setScreenCaptureResult(width, height, text);
        }
        stopScreenCapture();
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    void stopScreenCapture(){
        if (null != serviceConnection){
            unbindService(serviceConnection);
        }
        if (null != mediaProjection){
            mediaProjection.stop();
            mediaProjection = null;
        }
        if (null != virtualDisplay){
            virtualDisplay.release();
            virtualDisplay = null;
        }
        serviceConnection = null;
        myBinder = null;
    }
}