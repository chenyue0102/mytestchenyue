package com.xixi.observeapp.network;

import com.google.gson.Gson;

import java.io.IOException;

import okhttp3.MediaType;
import okhttp3.RequestBody;
import retrofit2.Converter;

public class JsonRequestBodyConverter<T> implements Converter<T, RequestBody> {
    private static final Gson mGson = new Gson();
    private static final MediaType MEDIA_TYPE = MediaType.parse(Constants.HeaderContentType);
    @Override
    public RequestBody convert(T value) throws IOException {
        return RequestBody.create(MEDIA_TYPE, mGson.toJson(value));
    }
}
