package com.test.testcamera;

import android.opengl.GLES30;
import android.util.Log;

public class OpenGLHelper {
    public static void attachShader(int program, int shaderType, String shaderSource) throws Exception{
        int shader = 0;
        try {
            shader = GLES30.glCreateShader(shaderType);
            checkError();
            GLES30.glShaderSource(shader, shaderSource);
            checkError();
            GLES30.glCompileShader(shader);
            checkError();
            outputCompileShader(shader);
            GLES30.glAttachShader(program, shader);
            checkError();
        }finally {
            if (0 != shader){
                GLES30.glDeleteShader(shader);
            }
        }
    }

    public static void checkError() throws MyException{
        int err = GLES30.glGetError();
        if (GLES30.GL_NO_ERROR != err){
            throw new MyException(err);
        }
    }

    public static class MyException extends Exception{
        private int mCode;
        public MyException(int code){
            super();
            mCode = code;
        }

        int getCode(){
            return mCode;
        }
    }

    private static int[] status_params = new int[1];
    public static void outputCompileShader(int shader){
        GLES30.glGetShaderiv(shader, GLES30.GL_COMPILE_STATUS, status_params, 0);
        if (GLES30.GL_TRUE != status_params[0]){
            String log = GLES30.glGetShaderInfoLog(shader);
            Log.e("GLSL30", "shader:" + log);
        }
    }

    public static void outputProgramLog(int program){
        GLES30.glGetProgramiv(program, GLES30.GL_LINK_STATUS, status_params, 0);
        if (GLES30.GL_TRUE != status_params[0]){
            String log = GLES30.glGetProgramInfoLog(program);
            Log.e("GLSL30", "Program:" + log);
        }
    }
}
