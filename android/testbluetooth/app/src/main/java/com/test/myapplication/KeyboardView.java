package com.test.myapplication;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;


public class KeyboardView extends androidx.appcompat.widget.AppCompatTextView {
    private int mKeyCode = KeyEvent.KEYCODE_UNKNOWN;

    public KeyboardView(Context context) {
        super(context, null);
    }

    public KeyboardView(Context context,  AttributeSet attrs) {
        super(context, attrs);
        initAttr(context, attrs);
    }

    public KeyboardView(Context context,  AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        initAttr(context, attrs);
    }

    public int getKeyCode(){
        return mKeyCode;
    }

    private void initAttr(Context context, AttributeSet attrs){
        TypedArray array = context.obtainStyledAttributes(attrs, new int[]{android.R.attr.keycode});

        mKeyCode = array.getInt(0, 0);
        Log.e("test", "keycode:" + mKeyCode);
    }
}
