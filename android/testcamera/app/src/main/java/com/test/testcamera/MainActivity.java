package com.test.testcamera;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.hardware.camera2.CameraCharacteristics;
import android.media.CamcorderProfile;
import android.media.MediaMetadata;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Display;
import android.view.Surface;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

@SuppressWarnings("deprecation")
public class MainActivity extends AppCompatActivity implements Camera.PreviewCallback {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private static final int REQUEST_CODE = 1;
    private static final int REQUEST_READ_STORAGE_CODE = 2;
    private MySurfaceView glSurfaceView;
    private SurfaceView surfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        glSurfaceView = findViewById(R.id.gl_surface_view);
        surfaceView = findViewById(R.id.surface_view);
        findViewById(R.id.btn_camera_preview_java).setOnClickListener((v)->checkPermissionAndOpenCamera());
        findViewById(R.id.btn_camera_record_java).setOnClickListener(v->onRecordJava());
        findViewById(R.id.btn_stop_record_java).setOnClickListener(v->onStopRecordJava());
        findViewById(R.id.btn_record_c).setOnClickListener(v->onRecordC());
        findViewById(R.id.btn_stop_record_c).setOnClickListener(v->onStopRecordC());

        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, REQUEST_READ_STORAGE_CODE);
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, REQUEST_READ_STORAGE_CODE);
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.RECORD_AUDIO}, REQUEST_READ_STORAGE_CODE);
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.INTERNET) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.INTERNET}, REQUEST_READ_STORAGE_CODE);
        }
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_NETWORK_STATE) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_NETWORK_STATE}, REQUEST_READ_STORAGE_CODE);
        }
        requestCameraPermissions();
    }

    private void requestCameraPermissions(){
        String[] requiredPermissions = {
                Manifest.permission.WRITE_EXTERNAL_STORAGE,
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.CAMERA,
        };
        ActivityCompat.requestPermissions(
                this,
                requiredPermissions,
                REQUEST_READ_STORAGE_CODE);
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

    private String getSDCardPath()throws Exception{
        String s;
        if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
            File sdDir = Environment.getExternalStorageDirectory();
            s = sdDir.getAbsolutePath();
        }else{
            throw new Exception("");
        }
        return s;
    }

    private void saveData(byte []data){
            boolean b = false;
            if (b){
                if (Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED)){
                    File sdDir = Environment.getExternalStorageDirectory();
                    String d = sdDir.getAbsolutePath();
                    try{
                        FileOutputStream fileOutputStream = new FileOutputStream(d + "/1.yuv.pcm");
                        fileOutputStream.write(data);
                        fileOutputStream.close();
                    }catch (Exception e){
                        e.printStackTrace();
                    }

                }
            }
    }

    @Override
    public void onPreviewFrame(byte[] data, Camera camera){
        try{
            glSurfaceView.setBuffer(data);
            saveData(data);
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

    public static Camera.Size getOptimalVideoSize(List<Camera.Size> supportedVideoSizes,
                                                  List<Camera.Size> previewSizes, int w, int h) {
        // Use a very small tolerance because we want an exact match.
        final double ASPECT_TOLERANCE = 0.1;
        double targetRatio = (double) w / h;

        // Supported video sizes list might be null, it means that we are allowed to use the preview
        // sizes
        List<Camera.Size> videoSizes;
        if (supportedVideoSizes != null) {
            videoSizes = supportedVideoSizes;
        } else {
            videoSizes = previewSizes;
        }
        Camera.Size optimalSize = null;

        // Start with max value and refine as we iterate over available video sizes. This is the
        // minimum difference between view and camera height.
        double minDiff = Double.MAX_VALUE;

        // Target view height
        int targetHeight = h;

        // Try to find a video size that matches aspect ratio and the target view size.
        // Iterate over all available sizes and pick the largest size that can fit in the view and
        // still maintain the aspect ratio.
        for (Camera.Size size : videoSizes) {
            double ratio = (double) size.width / size.height;
            if (Math.abs(ratio - targetRatio) > ASPECT_TOLERANCE)
                continue;
            if (Math.abs(size.height - targetHeight) < minDiff && previewSizes.contains(size)) {
                optimalSize = size;
                minDiff = Math.abs(size.height - targetHeight);
            }
        }

        // Cannot find video size that matches the aspect ratio, ignore the requirement
        if (optimalSize == null) {
            minDiff = Double.MAX_VALUE;
            for (Camera.Size size : videoSizes) {
                if (Math.abs(size.height - targetHeight) < minDiff && previewSizes.contains(size)) {
                    optimalSize = size;
                    minDiff = Math.abs(size.height - targetHeight);
                }
            }
        }
        return optimalSize;
    }

    MediaRecorder mMediaRecorder;
    private void onRecordJava(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{

                    if (false){
                        // BEGIN_INCLUDE (configure_preview)
                        mCamera = Camera.open();

                        // We need to make sure that our preview and recording video size are supported by the
                        // camera. Query camera to find all the sizes and choose the optimal size given the
                        // dimensions of our preview surface.
                        Camera.Parameters parameters = mCamera.getParameters();
                        List<Camera.Size> mSupportedPreviewSizes = parameters.getSupportedPreviewSizes();
                        List<Camera.Size> mSupportedVideoSizes = parameters.getSupportedVideoSizes();
                        Camera.Size optimalSize = getOptimalVideoSize(mSupportedVideoSizes,
                                mSupportedPreviewSizes, surfaceView.getWidth(), surfaceView.getHeight());


                        // Use the same size for recording profile.
                        CamcorderProfile profile = CamcorderProfile.get(CamcorderProfile.QUALITY_HIGH);
                        profile.videoFrameWidth = 864;
                        profile.videoFrameHeight = 480;

                        // likewise for the camera object itself.
                        parameters.setPreviewSize(profile.videoFrameWidth, profile.videoFrameHeight);
                        mCamera.setParameters(parameters);
                        try {
                            // Requires API level 11+, For backward compatibility use {@link setPreviewDisplay}
                            // with {@link SurfaceView}
                            mCamera.setPreviewDisplay(surfaceView.getHolder());
                        } catch (IOException e) {
                            e.printStackTrace();
                            return ;
                        }
                        // END_INCLUDE (configure_preview)


                        // BEGIN_INCLUDE (configure_media_recorder)
                        mMediaRecorder = new MediaRecorder();

                        // Step 1: Unlock and set camera to MediaRecorder
                        mCamera.unlock();
                        mMediaRecorder.setCamera(mCamera);

                        // Step 2: Set sources
                        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.DEFAULT );
                        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.CAMERA);

                        // Step 3: Set a CamcorderProfile (requires API Level 8 or higher)
                        mMediaRecorder.setProfile(profile);

                        // Step 4: Set output file
                        mMediaRecorder.setOutputFile("/storage/emulated/0/Pictures/CameraSample/test.mp4");
                        // END_INCLUDE (configure_media_recorder)

                        // Step 5: Prepare configured MediaRecorder
                        try {
                            mMediaRecorder.prepare();
                            mMediaRecorder.start();
                        } catch (IllegalStateException e) {
                            e.printStackTrace();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }else{
                        int width = 1920, height = 1080;
                        mCamera = Camera.open();
                        Camera.Parameters parameters = mCamera.getParameters();
                        List<Camera.Size> mSupportedPreviewSizes = parameters.getSupportedPreviewSizes();
                        List<Camera.Size> mSupportedVideoSizes = parameters.getSupportedVideoSizes();
                        parameters.setPreviewSize(width, height);
                        mCamera.setParameters(parameters);
                        mCamera.setPreviewDisplay(surfaceView.getHolder());

                        CamcorderProfile camcorderProfile = CamcorderProfile.get(CamcorderProfile.QUALITY_HIGH);
                        camcorderProfile.videoFrameWidth = width;
                        camcorderProfile.videoFrameHeight = height;

                        mMediaRecorder = new MediaRecorder();
                        mCamera.unlock();
                        mMediaRecorder.setCamera(mCamera);
                        mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.CAMERA);
                        mMediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);

                        //mMediaRecorder.setProfile(camcorderProfile);

                        mMediaRecorder.setVideoEncodingBitRate(1 * 1024 * 1024);
                        mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.MPEG_4);
                        mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.H264);
                        mMediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.HE_AAC);

                        mMediaRecorder.setVideoSize(width, height);
                        //mMediaRecorder.setOrientationHint(cameraInfo.orientation);
                        mMediaRecorder.setVideoFrameRate(24);

                        mMediaRecorder.setAudioEncodingBitRate(384000);
                        mMediaRecorder.setAudioChannels(2);
                        mMediaRecorder.setAudioSamplingRate(44100);

                        String saveFile = "/storage/emulated/0/Pictures/CameraSample/test.mp4";
                        mMediaRecorder.setOutputFile(saveFile);

                        mMediaRecorder.prepare();
                        mMediaRecorder.start();
                    }
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private void onStopRecordJava(){
        mMediaRecorder.stop();
    }

    private void onRecordC(){
        recordC("/storage/emulated/0/output.mp3");
    }

    private void onStopRecordC(){
        stopRecordC();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void recordC(String filePath);

    public native void stopRecordC();
}
