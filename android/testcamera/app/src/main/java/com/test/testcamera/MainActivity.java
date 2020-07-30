package com.test.testcamera;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.ActivityManager;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.os.Bundle;
import android.widget.TextView;

import java.io.InputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

@SuppressWarnings("deprecation")
public class MainActivity extends AppCompatActivity implements Camera.PreviewCallback {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    private static final int REQUEST_CODE = 1;
    private static final int REQUEST_READ_STORAGE_CODE = 2;
    private MySurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
        glSurfaceView = findViewById(R.id.gl_surface_view);
        findViewById(R.id.btn_camera_java).setOnClickListener((v)->checkPermissionAndOpenCamera());

        Timer timer = new Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(()->{
                    com.android.tradefed.device.CpuStatsCollector s;
                    float f = DeviceUtil.getCpuUsed();
                    tv.setText("cpu:" + f * 100 + "%");
                });
            }
        }, 0, 1000);

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, REQUEST_READ_STORAGE_CODE);
        }
    }

    public void checkPermissionAndOpenCamera(){
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.CAMERA}, REQUEST_CODE);
        }else{
            openCamera();
        }
    }

    public static boolean isAllPermissionsGranted(int []grantResults){
        for (int result : grantResults){
            if (PackageManager.PERMISSION_GRANTED != result){
                return false;
            }
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,  String[] permissions,  int[] grantResults) {
        if (requestCode == REQUEST_CODE){
            if (isAllPermissionsGranted(grantResults)){
                openCamera();
            }
        }
    }

    public static class CompareSizesByArea implements Comparator<Camera.Size> {

        @Override
        public int compare(Camera.Size lhs, Camera.Size rhs) {
            // We cast here to ensure the multiplications won't overflow
            return Long.signum((long) lhs.width * lhs.height -
                    (long) rhs.width * rhs.height);
        }

    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera){
        try{
            glSurfaceView.setBuffer(data);
        }catch (Exception e){
            e.printStackTrace();
        }
        runOnUiThread(()->glSurfaceView.requestRender());
    }

    private byte[] loadAssetsFile(String fileName)throws Exception{
        InputStream is = getAssets().open("vertex.glsl");
        int length = is.available();
        byte []buf = new byte[length];
        is.read(buf);
        return buf;
    }

    Camera mCamera;
    private void openCamera(){
        try{
            mCamera = Camera.open(Camera.CameraInfo.CAMERA_FACING_BACK);
            Camera.Parameters parameters = mCamera.getParameters();
            parameters.setPreviewFormat(ImageFormat.NV21);
            List<Camera.Size> sizes =  parameters.getSupportedPictureSizes();
            Camera.Size largestRaw = Collections.max(sizes, new CompareSizesByArea());
            parameters.setPictureSize(largestRaw.width, largestRaw.height);
            Camera.Size previewSize =  parameters.getPreviewSize();
            mCamera.setParameters(parameters);
            mCamera.setPreviewCallback(this);

            glSurfaceView.setInfo(previewSize.width, previewSize.height, ImageFormat.NV21);

            mCamera.startPreview();
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    //public native String stringFromJNI();
}
