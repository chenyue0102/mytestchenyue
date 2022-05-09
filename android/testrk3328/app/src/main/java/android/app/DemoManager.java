package android.app;

import android.content.Context;

public class DemoManager{
    private static final String TAG = "Demo";
    private Context mContext;
    private IDemoManager mService;

    public DemoManager(Context context, IDemoManager service){
        throw new RuntimeException("Stub!");
    }

    public int sum(int a, int b){
        throw new RuntimeException("Stub!");
    }

    public String getText(String str){
        throw new RuntimeException("Stub!");
    }
}