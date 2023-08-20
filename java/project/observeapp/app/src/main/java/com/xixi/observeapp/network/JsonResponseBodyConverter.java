package com.xixi.observeapp.network;

import android.util.Log;

import com.google.gson.Gson;
import com.xixi.observeapp.bean.Result;

import java.io.IOException;
import java.io.Reader;
import java.lang.reflect.Type;

import okhttp3.ResponseBody;
import retrofit2.Converter;

public class JsonResponseBodyConverter<T> implements Converter<ResponseBody, T> {
    private static final String TAG = "JsonResponseBodyConverter";
    private static final Gson mGson = new Gson();
    private Type mType;

    public JsonResponseBodyConverter(Type type){
        mType = type;
    }

    @Override
    public T convert(ResponseBody value) throws IOException {
        T result = null;
        try{
            String json = value.string();
            result = mGson.fromJson(json, mType);
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }
}
