package com.xixi.observeapp.network;

import com.xixi.observeapp.bean.LoginResult;
import com.xixi.observeapp.bean.RefreshTokenResult;
import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.bean.ServiceRandomResult;
import com.xixi.observeapp.bean.VerifyCodeResult;

import io.reactivex.Observable;
import okhttp3.RequestBody;
import retrofit2.http.Body;
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

    @Headers(Constants.HeaderContentType)
    @POST("login")
    Observable<Result<LoginResult>> login(@Body RequestBody requestBody);

    @Headers(Constants.HeaderContentType)
    @POST("refreshtoken")
    Observable<Result<RefreshTokenResult>> refreshToken(@Body RequestBody requestBody);

    @Headers(Constants.HeaderContentType)
    @POST("verifycode")
    Observable<Result<VerifyCodeResult>> getVerifyCode();
}
