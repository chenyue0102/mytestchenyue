package com.test.testspine;

import android.view.KeyEvent;

import org.libsdl.app.SDLActivity;

public class MySDLActivity extends SDLActivity {
    @Override
    protected String[] getLibraries(){
        return new String[]{
                "SDL2",
                "native-lib"
        };
    }

    @Override
    public void onBackPressed(){
        super.onBackPressed();
        finish();
    }

    @Override
    public boolean dispatchKeyEvent(KeyEvent event){
        if (event.getKeyCode() == KeyEvent.KEYCODE_BACK){
            finish();
            return true;//已经处理了
        }
        return super.dispatchKeyEvent(event);
    }
}
