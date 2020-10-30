package com.example.spinedemo;

import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;

import com.ksstory.spinewrap.BaseTime;
import com.ksstory.spinewrap.BatchRenderHelper;
import com.ksstory.spinewrap.RenderCmdsCache;
import com.ksstory.spinewrap.Skeleton;
import com.ksstory.spinewrap.SpineItem;
import com.ksstory.spinewrap.TextureLoader;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class SpineActivity extends AppCompatActivity {

    /////////////////////////////
    //在opengles线程中使用
    private BaseTime mBaseTime = new BaseTime();
    private long mLastTime = 0;
    private ArrayList<SpineItem> mSpineItems = new ArrayList<>();
    private RenderCmdsCache mRender = new RenderCmdsCache();
    private TextureLoader mTextureLoader = new TextureLoader();
    ////////////////////////////////////////////

    private Timer mRefreshTimer;
    private static final int FPS = 30;
    private GLSurfaceView mSurfaceView;

    public static String copyAssetsFile2Phone(Activity activity, String fileName){
        String path = null;
        try {
            InputStream inputStream = activity.getAssets().open(fileName);
            //getFilesDir() 获得当前APP的安装路径 /data/data/包名/files 目录
            path = activity.getFilesDir().getAbsolutePath() + File.separator + fileName;
            File file = new File(path);
            if(!file.exists() || file.length()==0) {
                FileOutputStream fos =new FileOutputStream(file);//如果文件不存在，FileOutputStream会自动创建文件
                int len=-1;
                byte[] buffer = new byte[1024];
                while ((len=inputStream.read(buffer))!=-1){
                    fos.write(buffer,0,len);
                }
                fos.flush();//刷新缓存区
                inputStream.close();
                fos.close();
            } else {
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return path;
    }

    private void copyAssets(){
        String dir  = getFilesDir().getAbsolutePath() + File.separator + "shader";
        File file = new File(dir);
        if (!file.exists()){
            file.mkdir();
        }
        String path = getFilesDir().getAbsolutePath() + File.separator;
        String fileNames[] = new String[]{
                "shader/texture.vert",
                "shader/texture.frag",
                "shader/color.vert",
                "shader/color.frag",
                "alien.atlas",
                "alien.png",
                "alien-ess.json"
        };
        for (String name : fileNames){
            copyAssetsFile2Phone(this, name);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_spine);

        copyAssets();

        mSurfaceView = findViewById(R.id.surfaceview);
        mSurfaceView.setEGLContextClientVersion(3);
        mSurfaceView.setRenderer(new GLSurfaceView.Renderer() {
            @Override
            public void onSurfaceCreated(GL10 gl, EGLConfig config) {
                mSurfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
                String shaderPath = getFilesDir().getAbsolutePath() + File.separator + "shader/";
                String vTexture = shaderPath + "texture.vert";
                String fTexture = shaderPath + "texture.frag";
                String vColor = shaderPath + "color.vert";
                String fColor = shaderPath + "color.frag";
                mRender.initShaderProgram(vTexture, fTexture, vColor, fColor);
            }

            @Override
            public void onSurfaceChanged(GL10 gl, int width, int height) {
                //屏幕旋转的时候，也需要处理宽高
                mRender.setViewSize((float)width, (float)height);
            }

            @Override
            public void onDrawFrame(GL10 gl) {
                mRender.render();
            }
        });

        findViewById(R.id.btn_add_alien).setOnClickListener(v->onAddAlien());
        findViewById(R.id.btn_gc).setOnClickListener(v->onGC());


        mRefreshTimer = new Timer();
        mRefreshTimer.schedule(new TimerTask() {
            @Override
            public void run() {
                mSurfaceView.queueEvent(new Runnable() {
                    @Override
                    public void run() {
                        //需要在opengl线程中运行
                        long curTime = mBaseTime.getCurrentTimeMs();
                        float delta = (float)(curTime - mLastTime) / 1000;
                        mBaseTime.getCurrentTimeMs();
                        for (SpineItem spineItem : mSpineItems){
                            spineItem.updateSkeletonAnimation(delta);
                        }
                        BatchRenderHelper.batchRender(mSpineItems, mRender);
                        mLastTime = curTime;

                        mSurfaceView.requestRender();
                    }
                });
            }
        }, 0, 1000 / FPS);

        mLastTime = mBaseTime.getCurrentTimeMs();
    }

    @Override
    protected void onDestroy(){
        mRefreshTimer.cancel();
        super.onDestroy();
    }

    private void onAddAlien(){
        mSurfaceView.queueEvent(new Runnable() {
            @Override
            public void run() {
                String spinePath = getFilesDir().getAbsolutePath() + File.separator;
                SpineItem spineItem = new SpineItem();
                spineItem.setAtlasFile(spinePath + "alien.atlas");
                spineItem.setSkeletonFile(spinePath + "alien-ess.json");
                spineItem.create(mTextureLoader);
                spineItem.setAnimation(0, "death", true);
                Skeleton skeleton = spineItem.getSkeleton();
                double x = (Math.random() - 0.5) * 300, y = (Math.random() - 0.5) * 500;
                skeleton.setPosition((float)x, (float)y);
                mSpineItems.add(spineItem);
            }
        });
    }

    private void onGC(){
        System.gc();
    }
}