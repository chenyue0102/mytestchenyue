package com.xixi.observeapp.network;

import android.app.Application;
import android.text.TextUtils;
import android.util.Log;

import com.google.gson.Gson;
import com.xixi.observeapp.MyApplication;
import com.xixi.observeapp.bean.RefreshTokenRequest;
import com.xixi.observeapp.bean.RefreshTokenResult;
import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.constants.Constants;
import com.xixi.observeapp.util.SpUtils;

import org.json.JSONObject;
import org.w3c.dom.Text;

import java.io.IOException;
import java.util.concurrent.TimeUnit;

import okhttp3.Interceptor;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Call;
import retrofit2.Retrofit;
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory;

public class TokenInterceptor implements Interceptor {
    private static final String TAG = "TokenInterceptor";
    @Override
    public Response intercept(Chain chain) throws IOException {
        Request request = chain.request();
        Response response = chain.proceed(request);
        String json = response.body().string();
        if (isTokenExpired(json)){
            String newToken = getNewToken();
            if (TextUtils.isEmpty(newToken)){
                return response.newBuilder()
                        .body(ResponseBody.create(response.body().contentType(), json))
                        .build();
            }
            Request newRequest = chain.request()
                    .newBuilder()
                    .header("token", newToken)
                    .build();
            return chain.proceed(newRequest);
        }
        return response.newBuilder()
                .body(ResponseBody.create(response.body().contentType(), json))
                .build();
    }

    private boolean isTokenExpired(String json){
        boolean expired = false;
        try{
            Log.w(TAG, "~~~~~~~~~"+json);
            JSONObject object = new JSONObject(json);
            int code = object.optInt("code");
            expired = code == Result.CODE_ACCESS_TOKEN_EXPIRED;
        }catch (Exception e){
            e.printStackTrace();
        }
        return expired;
    }

    private String getNewToken() throws IOException {
        String newToken = "";
        HttpLoggingInterceptor loggingInterceptor = new HttpLoggingInterceptor();
        loggingInterceptor.setLevel(HttpLoggingInterceptor.Level.BODY);
        OkHttpClient okHttpClient = new OkHttpClient.Builder()
                .addInterceptor(loggingInterceptor)
                .connectTimeout(5, TimeUnit.SECONDS)
                .writeTimeout(5, TimeUnit.SECONDS)
                .readTimeout(5, TimeUnit.SECONDS)
                .build();
        Retrofit retrofit = new Retrofit.Builder()
                .baseUrl(Constants.BASE_URL)
                .addConverterFactory(JsonConverterFactory.create())
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .client(okHttpClient)
                .build();
        Gson gson = new Gson();
        RefreshTokenRequest refreshTokenRequest = new RefreshTokenRequest();
        String refreshToken = SpUtils.getString(MyApplication.getContext(), Constants.REFRESH_TOKEN_NAME);
        if (TextUtils.isEmpty(refreshToken)){
            return "";
        }
        refreshTokenRequest.setRefreshToken(refreshToken);
        RequestBody requestBody = RequestBody.create(MediaType.parse(Constants.HeaderContentType), gson.toJson(refreshTokenRequest));
        Call<ResponseBody> call = (Call<ResponseBody>)retrofit.create(ObserveService.class).refreshToken(requestBody);
        String jsonText = call.execute().body().string();
        Result< RefreshTokenResult > tmp = new Result< RefreshTokenResult >();
        Result<RefreshTokenResult> result = gson.fromJson(jsonText, tmp.getClass());
        return result.getData().getAccessToken();
    }
}
