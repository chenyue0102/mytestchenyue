package com.example.testcplusplus;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI() + MainActivity.stringFromJNI2());

        int v = string2Int("1234");
        Log.i("MyTest", ""+v);
        int iarray[] = new int[]{1,2,3,4,5,6,7,8,9};
        int top3[] = getTop3(iarray);
        Log.i("MyTest", "" + top3[0]+top3[1]+top3[2]);
        int iarray2[] = new int[]{1};
        top3 = getTop3(iarray2);
        Log.i("MyTest", "" + top3[0]+top3[1]+top3[2]);

        ByteBuffer b = getDirectBuffer();
        byte bbb[] = new byte[1024];
        b.get(bbb, 0, 1024);
        releaseDirectBuffer(b);
        bbb=null;
        b = null;
        testAccessField();
    }

    public String instanceField = new String("instanceField");
    public static String staticField = new String("staticField");
    public int test1(int a[], int b[]){return 0;}

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native static String stringFromJNI2();

    public native int string2Int(String s);

    public native int[] getTop3(int i[]);

    public native ByteBuffer getDirectBuffer();
    public native void releaseDirectBuffer(ByteBuffer b);

    public native void testAccessField();
}
