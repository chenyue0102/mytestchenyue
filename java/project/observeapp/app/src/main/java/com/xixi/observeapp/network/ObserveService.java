package com.xixi.observeapp.network;

import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.bean.ServiceRandomResult;

import retrofit2.http.GET;
import retrofit2.http.Headers;

public interface ObserveService {
    @Headers(Constants.HeaderContentType)
    @GET("/random")
    Result<ServiceRandomResult> getServiceRandom();
}
