package com.xixi.observeapp.network;

import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.bean.ServiceRandomResult;

import io.reactivex.Observable;
import retrofit2.http.GET;
import retrofit2.http.Headers;
import retrofit2.http.POST;

public interface ObserveService {

    public static class TestJson{
        public String text;
    }
    @Headers(Constants.HeaderContentType)
    @GET("testjson")
    Observable<Result<TestJson>> getTestJson();

    @Headers(Constants.HeaderContentType)
    @POST("random")
    Observable<Result<ServiceRandomResult>> getServiceRandom();
}
