package com.test.testcamera;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.os.Bundle;
import android.view.Display;
import android.view.Surface;
import android.view.SurfaceView;
import android.widget.TextView;

import java.io.InputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

@SuppressWarnings("deprecation")
public class MainActivity extends AppCompatActivity implements Camera.PreviewCallback {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    private static final int REQUEST_CODE = 1;
    private static final int REQUEST_READ_STORAGE_CODE = 2;
    private MySurfaceView glSurfaceView;
    private SurfaceView surfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
        glSurfaceView = findViewById(R.id.gl_surface_view);
        surfaceView = findViewById(R.id.surface_view);
        findViewById(R.id.btn_camera_java).setOnClickListener((v)->checkPermissionAndOpenCamera());

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, REQUEST_READ_STORAGE_CODE);
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_READ_STORAGE_CODE);
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
//            boolean b = false;
//            if (b){
//                if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
//                    File sdDir = Environment.getExternalStorageDirectory();
//                    String d = sdDir.getAbsolutePath();
//                    try{
//                        FileOutputStream fileOutputStream = new FileOutputStream(d + "/1.yuv");
//                        fileOutputStream.write(data);
//                        fileOutputStream.close();
//                    }catch (Exception e){
//                        e.printStackTrace();
//                    }
//
//                }
//            }
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
            Camera.CameraInfo cameraInfo = new Camera.CameraInfo();
            Camera.getCameraInfo(Camera.CameraInfo.CAMERA_FACING_BACK, cameraInfo);
            int angle;
            Display display = getWindowManager().getDefaultDisplay();
            switch (display.getRotation()) {
                case Surface.ROTATION_0: // This is display orientation
                    angle = 90; // This is camera orientation
                    break;
                case Surface.ROTATION_90:
                    angle = 0;
                    break;
                case Surface.ROTATION_180:
                    angle = 270;
                    break;
                case Surface.ROTATION_270:
                    angle = 180;
                    break;
                default:
                    angle = 90;
                    break;
            }

            mCamera.setDisplayOrientation(angle);
            mCamera.setParameters(parameters);
            mCamera.setPreviewCallback(this);
            mCamera.setPreviewDisplay(surfaceView.getHolder());

            angle = (360 - cameraInfo.orientation) % 360;
            glSurfaceView.setInfo(previewSize.width, previewSize.height, ImageFormat.NV21, angle);

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
