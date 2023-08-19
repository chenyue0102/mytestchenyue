package com.xixi.observeapp.network;

import java.lang.reflect.Proxy;
import java.util.concurrent.TimeUnit;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Retrofit;
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory;

public class ApiManager {
    public static final int TIMEOUT_SECOND = 10;
    private static volatile ApiManager instance;
    private OkHttpClient okHttpClient;

    private Retrofit retrofit;

    private ApiManager(){
        initOkHttp();
        initRetrofit();
    }

    public static ApiManager getInstance(){
        if (null == instance){
            synchronized (ApiManager.class){
                if (null == instance){
                    instance = new ApiManager();
                }
            }
        }
        return instance;
    }

    public static Request.Builder headerJoin(Request.Builder builder){
        return builder;
    }

    private void initOkHttp(){
        OkHttpClient.Builder builder = new OkHttpClient().newBuilder()
                .connectTimeout(TIMEOUT_SECOND, TimeUnit.SECONDS)
                .readTimeout(TIMEOUT_SECOND, TimeUnit.SECONDS)
                .writeTimeout(TIMEOUT_SECOND, TimeUnit.SECONDS)
                .addInterceptor(chain -> {
                    Request request = headerJoin(chain.request().newBuilder())
                            .method(chain.request().method(), chain.request().body())
                            .build();
                    return chain.proceed(request);
                });

        HttpLoggingInterceptor httpLoggingInterceptor = new HttpLoggingInterceptor();
        httpLoggingInterceptor.setLevel(HttpLoggingInterceptor.Level.BODY);
        builder.addInterceptor(httpLoggingInterceptor);

        okHttpClient = builder.build();
        okHttpClient.dispatcher().setMaxRequestsPerHost(10);
    }

    private void initRetrofit(){
        Retrofit.Builder builder = new Retrofit.Builder();
        retrofit = builder
                .baseUrl(Constants.BASE_URL)
                .client(okHttpClient)
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .addConverterFactory(JsonConverterFactory.create())
                .build();
    }

    public <T> T getProxy(Class<T> tClass){
        T t = getInstance().retrofit.create(tClass);
        return t;
    }
}
