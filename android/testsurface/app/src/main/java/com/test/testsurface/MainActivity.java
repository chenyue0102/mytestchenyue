package com.test.testsurface;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.annotation.RequiresPermission;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.annotation.TargetApi;
import android.content.Context;
import android.content.pm.PackageManager;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.hardware.camera2.CameraAccessException;
import android.hardware.camera2.CameraCaptureSession;
import android.hardware.camera2.CameraCharacteristics;
import android.hardware.camera2.CameraDevice;
import android.hardware.camera2.CameraManager;
import android.hardware.camera2.CameraMetadata;
import android.hardware.camera2.CaptureRequest;
import android.hardware.camera2.CaptureResult;
import android.hardware.camera2.TotalCaptureResult;
import android.hardware.camera2.params.StreamConfigurationMap;
import android.media.AudioDeviceInfo;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.Image;
import android.media.ImageReader;
import android.media.MediaRecorder;
import android.media.MediaSyncEvent;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.storage.StorageManager;
import android.provider.MediaStore;
import android.util.Log;
import android.util.Size;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.widget.Button;
import android.widget.TextView;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.security.PublicKey;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.PrimitiveIterator;

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

        ActivityCompat.requestPermissions(this, new String[]{
                Manifest.permission.CAMERA,
                Manifest.permission.RECORD_AUDIO,
                Manifest.permission.READ_EXTERNAL_STORAGE,
                Manifest.permission.WRITE_EXTERNAL_STORAGE}, 100);

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
        findViewById(R.id.btn_audio).setOnClickListener(v->openAudio());
        findViewById(R.id.btn_exit).setOnClickListener(v->mExit = true);
        findViewById(R.id.btn_record_audio).setOnClickListener(v->onRecordAudio());
        findViewById(R.id.btn_stop_record_audio).setOnClickListener(v->onStopRecordAudio());
        findViewById(R.id.btn_play_audio).setOnClickListener(v->onPlayAudio());
        findViewById(R.id.btn_stop_play_audio).setOnClickListener(v->onStopPlayAudio());
        findViewById(R.id.btn_record_video).setOnClickListener(v->onRecordVideo());
        findViewById(R.id.btn_stop_record_video).setOnClickListener(v->onStopRecordVideo());
        findViewById(R.id.btn_open_camera1).setOnClickListener(v->openCamear1());

        //if (requestCamera(Manifest.permission.CAMERA, PERMISSION_REQUEST_CODE_CAMERA)) {
//            if (!isCamera2Device()) {
//                Log.i("tag", "not support");
//            }
//            if (ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
//                return;
//            }
            //openCamera();
       // }
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
                }else{
                    Log.i("tag", "support");
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
    private AudioRecord mAudioRecord;
    private static final int IMAGE_FORMAT = ImageFormat.YUV_420_888;
    private boolean mFirst = true;
    private boolean mExit = false;

    /**
     * captureType CameraDevice.TEMPLATE_PREVIEW
     * @param captureType
     * @param surfaces
     */
    private void createCameraPreviewSession(int captureType, Surface[]surfaces){
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

            mCaptureRequestBuilder = mCameraDevice.createCaptureRequest(captureType);
//            SurfaceHolder surfaceHolder = surfaceView.getHolder();
//            Surface surface = surfaceHolder.getSurface();
            for (Surface surface : surfaces){
                mCaptureRequestBuilder.addTarget(surface);
            }
            //mCaptureRequestBuilder.addTarget(mSurface);
            //mCaptureRequestBuilder.addTarget(mImageReader.getSurface());

            mCameraDevice.createCaptureSession(Arrays.asList(/*mSurface, mImageReader.getSurface()*/surfaces), new CameraCaptureSession.StateCallback() {
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
                Size[]sizes = map.getOutputSizes(IMAGE_FORMAT);
                Size largestRaw = Collections.max(Arrays.asList(sizes), new CompareSizesByArea());
                mImageReader = ImageReader.newInstance(largestRaw.getWidth(), largestRaw.getHeight(), IMAGE_FORMAT, 5);
                mImageReader.setOnImageAvailableListener(reader -> {
                    Image image = null;
                    try{
                        image = mImageReader.acquireNextImage();
                        Image.Plane[] planes = image.getPlanes();
                        Log.i(TAG, "planes count:" + planes.length);
//                        if (mFirst){
//                            mFirst = false;
//                            File file = new File("/storage/emulated/0/text.yuv");
//                            if (!file.exists()){
//                                file.createNewFile();
//                            }
//                            RandomAccessFile raf = new RandomAccessFile(file, "rwd");
//                            for (Image.Plane plane : planes){
//                                ByteBuffer byteBuffer = plane.getBuffer();
//                                byte []bytes = new byte[byteBuffer.remaining()];
//                                byteBuffer.get(bytes);
//                                raf.write(bytes);
//                            }
//                            raf.close();
//                        }
                    }catch (Exception e){
                        e.printStackTrace();
                    }finally {
                        if (null != image){
                            image.close();
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
                    createCameraPreviewSession(CameraDevice.TEMPLATE_RECORD, new Surface[]{mSurface, mImageReader.getSurface()});
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

    private void printAudioRecord(){
        int audioSource = MediaRecorder.AudioSource.MIC;
        int []sampleRates = new int[]{8000, 11025, 22050, 44100};
        int []audioFormats = new int[]{AudioFormat.ENCODING_PCM_8BIT, AudioFormat.ENCODING_PCM_16BIT, AudioFormat.ENCODING_PCM_FLOAT};
        int []channelConfigs = new int[]{AudioFormat.CHANNEL_IN_MONO, AudioFormat.CHANNEL_IN_STEREO };
        for (int sampleRate : sampleRates){
            for (int audioFormat : audioFormats){
                for (int channelConfig : channelConfigs){
                    int bufferSize = AudioRecord.getMinBufferSize(sampleRate, channelConfig, audioFormat);
                    AudioRecord audioRecord = new AudioRecord(audioSource, sampleRate, channelConfig, audioFormat, bufferSize);
                    if (audioRecord.getState() == AudioRecord.STATE_INITIALIZED){
                        String strFormat = "";
                        switch (audioFormat){
                            case AudioFormat.ENCODING_PCM_8BIT:
                                strFormat = "8bit";
                                break;
                            case AudioFormat.ENCODING_PCM_16BIT:
                                strFormat = "16bit";
                                break;
                            case AudioFormat.ENCODING_PCM_FLOAT:
                                strFormat = "float";
                                break;
                        }
                        Log.i(TAG, "printAudioRecord sampleRates:" + sampleRate + " audioFormats:" + strFormat + " channelConfig:" +
                                (channelConfig == AudioFormat.CHANNEL_IN_MONO ? "mono" : "stereo"));
                    }
                }
            }
        }
    }

    /*
    //http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
    struct wav_header_t
    {
        char chunkID[4]; //"RIFF" = 0x46464952
        uint32_t chunkSize; //文件长度-8
        char format[4]; //"WAVE" = 0x45564157
        char subchunk1ID[4]; //"fmt " = 0x20746D66
        uint32_t subchunk1Size; //16 18 40 [+ sizeof(wExtraFormatBytes) + wExtraFormatBytes]
        uint16_t audioFormat;//数据类型,"01 00"表示 PCM
        uint16_t numChannels;//通道数
        uint32_t sampleRate;//采样率，比如""表示44100采样率
        uint32_t byteRate;//码率： 采样率x位深度x通道数/8 比如双通道的44.1K 16位采样的码率为176400
        uint16_t blockAlign;//采样一次，占内存大小 ： 位深度x通道数/8
        uint16_t bitsPerSample;//采样深度

        uint16_t cbSize;//Size of the extension (0 or 22)

        uint16_t wValidBitsPerSample;//Number of valid bits
        uint32_t dwChannelMask;//Speaker position mask
        uint8_t SubFormat[16];//GUID including the data format code
    };
    struct chunk_t
    {
        char ID[4]; //"data" = 0x61746164
        unsigned long size;  //Chunk data bytes
    };
    //All (compressed) non-PCM formats must have a fact chunk (Rev. 3 documentation). The chunk contains at least one value, the number of samples in the file.
    struct fact_chunk_t {
        char ckID[4];//"fact"
        uint32_t cksize;//Chunk size: minimum 4
        uint32_t dwSampleLength;//Number of samples (per channel)
    };
     */

    private static final int WAV_MIN_FACT_CHUNK_LENGTH = 4 + 4 + 4;
    private static final int WAV_CHUNK_HEADER_LENGTH = 4 + 4;
    private static final int WAV_MIN_HEADER_LENGTH = 36 + 8;
    private static final int SAMPLE_FORMAT_PCM_8BIT = 1;
    private static final int SAMPLE_FORMAT_PCM_16BIT = 2;
    private static final int SAMPLE_FORMAT_PCM_FLOAT = 3;
    private int getHeaderLength(int sampleFormat){
        return sampleFormat == SAMPLE_FORMAT_PCM_FLOAT ? WAV_MIN_HEADER_LENGTH + 12 : WAV_MIN_HEADER_LENGTH;
    }

    private byte[] getWavHeader(int wavDataBytes, int numChannels, int sampleRate, int sampleFormat){
        int bitsPerSample = 0, audioFormat = 0;
        switch (sampleFormat){
            case SAMPLE_FORMAT_PCM_8BIT:
                audioFormat = 1;//WAVE_FORMAT_PCM
                bitsPerSample = 8;
                break;
            case SAMPLE_FORMAT_PCM_16BIT:
                audioFormat = 1;//WAVE_FORMAT_PCM
                bitsPerSample = 16;
                break;
            case SAMPLE_FORMAT_PCM_FLOAT:
                audioFormat = 3;//WAVE_FORMAT_IEEE_FLOAT
                bitsPerSample = 32;
                break;
        }
        int headerLen = getHeaderLength(sampleFormat);

        byte []data = new byte[headerLen];
        ByteBuffer byteBuffer = ByteBuffer.wrap(data);
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN);
        //wav header
        byteBuffer.putInt(0x46464952);//chunkID
        byteBuffer.putInt(wavDataBytes + headerLen - 8);//chunkSize
        byteBuffer.putInt(0x45564157);//format
        byteBuffer.putInt(0x20746D66);//subchunk1ID
        byteBuffer.putInt(sampleFormat == SAMPLE_FORMAT_PCM_FLOAT ? 40 : 16);//subchunk1Size
        byteBuffer.putShort((short) audioFormat);//audioFormat
        byteBuffer.putShort((short) numChannels);//numChannels
        byteBuffer.putInt(sampleRate);//sampleRate
        byteBuffer.putInt(sampleRate * numChannels * bitsPerSample / 8);//byteRate
        byteBuffer.putShort((short)(bitsPerSample * numChannels / 8));//blockAlign
        byteBuffer.putShort((short) bitsPerSample);//bitsPerSample

        if (audioFormat != 1){
            //not WAVE_FORMAT_PCM
            byteBuffer.putInt(0x74636166);//fact
            byteBuffer.putInt(4);//cksize
            int dwSampleLength = wavDataBytes / numChannels / bitsPerSample * 8;//Number of samples (per channel)
            byteBuffer.putInt(dwSampleLength);
        }

        //chunk
        byteBuffer.putInt(0x61746164);
        byteBuffer.putInt(wavDataBytes);
        byteBuffer.flip();
        return data;
    }



    private void openAudio(){
        int audioSource = MediaRecorder.AudioSource.MIC;
        int sampleRateInHz = 44100;
        int channelConfig = AudioFormat.CHANNEL_IN_STEREO ;
        int audioFormat = AudioFormat.ENCODING_PCM_FLOAT;
        int bufferSizeInBytes = AudioRecord.getMinBufferSize(sampleRateInHz, channelConfig, audioFormat);
        mAudioRecord = new AudioRecord(audioSource, sampleRateInHz, channelConfig, audioFormat, bufferSizeInBytes);
        if (mAudioRecord.getState() != AudioRecord.STATE_INITIALIZED){
            Log.i(TAG, "AudioRecord failed");
            return;
        }
        mAudioRecord.startRecording();
        new Thread(() -> {
            File file = new File("/storage/emulated/0/test.wav");
            try{
                if (!file.exists()){
                    file.createNewFile();
                }
                RandomAccessFile randomAccessFile = new RandomAccessFile(file, "rwd");
                randomAccessFile.seek(getHeaderLength(SAMPLE_FORMAT_PCM_FLOAT));

                int totalWriteFloatCount = 0;
                float []buffer = new float[bufferSizeInBytes / 4];
                while(!mExit){
                    int len = mAudioRecord.read(buffer, 0, bufferSizeInBytes / 4, AudioRecord.READ_BLOCKING);
                    for (int i = 0;i < len; i++){
                        randomAccessFile.writeFloat(buffer[i]);
                        totalWriteFloatCount++;
                    }
                }
                byte []header = getWavHeader(totalWriteFloatCount * 4, 2, sampleRateInHz, SAMPLE_FORMAT_PCM_FLOAT);
                randomAccessFile.seek(0);
                randomAccessFile.write(header);
                randomAccessFile.close();
                Log.i(TAG, "record audio exit");
            }catch (IOException e){
                e.printStackTrace();
            }
        }).start();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private native void createCamera();

    private void onRecordAudio(){
        int deviceId = 6;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
            AudioManager audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
            AudioDeviceInfo[]deviceInfos = audioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
            deviceId = deviceInfos[0].getId();
        }
        File file = Environment.getExternalStorageDirectory();
        String filePath = file.toString() + "/test.pcm";
        recordAudio(deviceId, filePath);
    }

    private native void recordAudio(int deviceId, String fileName);

    private void onStopRecordAudio(){
        stopRecordAudio();
    }

    private native void stopRecordAudio();

    private void onPlayAudio(){
        int deviceId = 6;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M){
            AudioManager audioManager = (AudioManager)getSystemService(Context.AUDIO_SERVICE);
            AudioDeviceInfo[]deviceInfos = audioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
            deviceId = deviceInfos[0].getId();
        }
        File file = Environment.getExternalStorageDirectory();
        String filePath = file.toString() + "/test.pcm";
        playAudio(deviceId, filePath);
    }

    private native void playAudio(int deviceId, String filePath);

    private void onStopPlayAudio(){
        stopPlayAudio();
    }
    private native void stopPlayAudio();

    private void onRecordVideo(){
        try{
            File file = Environment.getExternalStorageDirectory();
            String filePath = file.toString() + "/test.yuv";
            //CameraManager cameraManager = (CameraManager)getSystemService(Context.CAMERA_SERVICE);
            //String []cameraIdList = cameraManager.getCameraIdList();
            recordVideo("0", 0, filePath);
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    private native void recordVideo(String cameraId, int templateId, String filePath);

    private void onStopRecordVideo(){
        stopRecordVideo();
    }
    private native void stopRecordVideo();

    private Camera mCamear;
    private void openCamear1(){
        mCamear = Camera.open(Camera.CameraInfo.CAMERA_FACING_BACK);
        Camera.Parameters parameters = mCamear.getParameters();
        parameters.setPreviewFormat(ImageFormat.NV21);
        List<Camera.Size> sizes = parameters.getSupportedVideoSizes();
    }
}
