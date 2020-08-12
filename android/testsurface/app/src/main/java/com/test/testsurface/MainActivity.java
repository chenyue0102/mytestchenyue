package com.test.testsurface;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresPermission;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.annotation.TargetApi;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.CaptureResult;
import android.hardware.camera2.TotalCaptureResult;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.Image;
import android.media.ImageReader;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.util.Log;
import android.util.Size;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.Button;
import android.widget.TextView;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";
    private static Handler mHandler;
    private static HandlerThread mHandlerThread;
    private TextureView textureView;

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    private static final int PERMISSION_REQUEST_CODE_CAMERA = 1;
    private SurfaceView surfaceView;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mHandlerThread = new HandlerThread("camera");
        mHandlerThread.start();
        mHandler = new Handler(mHandlerThread.getLooper());

        surfaceView = findViewById(R.id.surfaceView);
        textureView = findViewById(R.id.textureview);
        Button btnCreate = findViewById(R.id.btn_create);
        btnCreate.setOnClickListener((v) -> {
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            openCamera();
        });

        if (requestCamera(Manifest.permission.CAMERA, PERMISSION_REQUEST_CODE_CAMERA)) {
            if (!isCamera2Device()) {
                Log.i("tag", "not support");
            }
            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
                return;
            }
            //openCamera();
        }
    }

    private boolean isAllPermissionsGranted(int []grantResults){
        for (int result : grantResults){
            if (PackageManager.PERMISSION_GRANTED != result){
                return false;
            }
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode,  String[] permissions,  int[] grantResults) {
        if (requestCode == PERMISSION_REQUEST_CODE_CAMERA){
            if (isAllPermissionsGranted(grantResults)){
                if (!isCamera2Device()){
                    Log.i("tag", "not support");
                }
            }
        }
    }

    private boolean requestCamera(String permission, int permissionCode){
        if (ActivityCompat.checkSelfPermission(this, permission) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this,  new String[]{permission}, permissionCode);
            return false;
        }
        return true;
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    private boolean isCamera2Device(){
        try{
            CameraManager cameraManager = (CameraManager)getSystemService(Context.CAMERA_SERVICE);
            String []cameraIdList = cameraManager.getCameraIdList();
            for (String cameraId : cameraIdList){
                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(cameraId);
                int deviceLevel = cameraCharacteristics.get(CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL);
                int facing = cameraCharacteristics.get(CameraCharacteristics.LENS_FACING);
                if (deviceLevel == CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY && facing == CameraCharacteristics.LENS_FACING_BACK){
                    return false;
                }
            }
        }catch (Exception e){
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private CameraDevice mCameraDevice;
    private CameraCaptureSession mCameraCaptureSession;
    private CaptureRequest.Builder mCaptureRequestBuilder;
    private CameraCaptureSession.CaptureCallback mCaptureCallback;
    private ImageReader mImageReader;

    private void createCameraPreviewSession(){
        try{
            mCaptureCallback = new CameraCaptureSession.CaptureCallback(){

                @Override
                public void onCaptureProgressed(@NonNull CameraCaptureSession session,
                                                @NonNull CaptureRequest request,
                                                @NonNull CaptureResult partialResult) {
                    Log.i(TAG, "onCaptureProgressed");
                }
                @Override
                public void onCaptureCompleted(@NonNull CameraCaptureSession session,
                                               @NonNull CaptureRequest request,
                                               @NonNull TotalCaptureResult result) {
                    Log.i(TAG, "onCaptureCompleted");
                }
            };

            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(CameraDevice.TEMPLATE_PREVIEW);
            SurfaceHolder surfaceHolder = surfaceView.getHolder();
            Surface surface = surfaceHolder.getSurface();
            //mCaptureRequestBuilder.addTarget(mImageReader.getSurface());
            mCaptureRequestBuilder.addTarget(mSurface);

            mCameraDevice.createCaptureSession(Arrays.asList(mSurface), new CameraCaptureSession.StateCallback() {
                @Override
                public void onConfigured(@NonNull CameraCaptureSession session) {
                    mCameraCaptureSession = session;
                    if (null == mCameraCaptureSession){
                        return;
                    }
                    try{
                        mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AF_MODE, CaptureRequest.CONTROL_AF_MODE_CONTINUOUS_PICTURE);
                        CaptureRequest request = mCaptureRequestBuilder.build();
                        mCameraCaptureSession.setRepeatingRequest(request, mCaptureCallback, mHandler);
                        Log.i(TAG, "onConfigured ok");
                    }catch (Exception e){
                        e.printStackTrace();
                    }
                }

                @Override
                public void onConfigureFailed(@NonNull CameraCaptureSession session) {
                    Log.i(TAG, "onConfigureFailed");
                }
            }, mHandler);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private void unlockFocus(){
        try{
            mCaptureRequestBuilder.set(CaptureRequest.CONTROL_AF_TRIGGER, CameraMetadata.CONTROL_AF_TRIGGER_CANCEL);
            CaptureRequest request = mCaptureRequestBuilder.build();
            mCameraCaptureSession.capture(request, mCaptureCallback, mHandler);
            mCameraCaptureSession.setRepeatingRequest(request, mCaptureCallback, mHandler);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private Surface mSurface;
    static class CompareSizesByArea implements Comparator<Size> {

        @Override
        public int compare(Size lhs, Size rhs) {
            // We cast here to ensure the multiplications won't overflow
            return Long.signum((long) lhs.getWidth() * lhs.getHeight() -
                    (long) rhs.getWidth() * rhs.getHeight());
        }

    }
    @RequiresPermission(android.Manifest.permission.CAMERA)
    private void openCamera(){
        try{
            mSurface = new Surface(textureView.getSurfaceTexture());
            String cameraId = null;
            CameraManager cameraManager = (CameraManager)getSystemService(Context.CAMERA_SERVICE);
            String []cameraIdList = cameraManager.getCameraIdList();
            for (String tmpCameraId : cameraIdList){
                CameraCharacteristics cameraCharacteristics = cameraManager.getCameraCharacteristics(tmpCameraId);
                int deviceLevel = cameraCharacteristics.get(CameraCharacteristics.INFO_SUPPORTED_HARDWARE_LEVEL);
                int facing = cameraCharacteristics.get(CameraCharacteristics.LENS_FACING);
                if (facing != CameraCharacteristics.LENS_FACING_BACK){
                    continue;
                }
                cameraId = tmpCameraId;
                StreamConfigurationMap map = cameraCharacteristics.get(CameraCharacteristics.SCALER_STREAM_CONFIGURATION_MAP);
                Size[]sizes = map.getOutputSizes(ImageFormat.RAW_SENSOR);
                Size largestRaw = Collections.max(Arrays.asList(sizes), new CompareSizesByArea());
                mImageReader = ImageReader.newInstance(largestRaw.getWidth(), largestRaw.getHeight(), ImageFormat.RAW_SENSOR, 5);
                mImageReader.setOnImageAvailableListener(new ImageReader.OnImageAvailableListener(){
                    @Override
                    public void onImageAvailable(ImageReader reader) {
                        try{
                            Image image = mImageReader.acquireNextImage();
                        }catch (Exception e){
                            e.printStackTrace();
                        }
                    }
                }, mHandler);
                break;
            }
            cameraManager.openCamera(cameraId, new CameraDevice.StateCallback(){
                @Override
                public void onOpened(@NonNull CameraDevice camera) {
                    Log.i(TAG, "onOpened");
                    mCameraDevice = camera;
                    createCameraPreviewSession();
                }

                @Override
                public void onDisconnected(@NonNull CameraDevice camera) {
                    Log.i(TAG, "onDisconnected");
                }

                @Override
                public void onError(@NonNull CameraDevice camera, int error) {
                    Log.i(TAG, "onError");
                }
            }, mHandler);
            cameraManager.registerAvailabilityCallback( new CameraManager.AvailabilityCallback(){
                @Override
                public void onCameraAvailable(@NonNull String cameraId) {
                    Log.i(TAG, "onCameraAvailable");
                }
                @Override
                public void onCameraUnavailable(@NonNull String cameraId) {
                    Log.i(TAG, "onCameraUnavailable");
                }
            }, mHandler);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private native void createCamera();
}
