package com.example.testokhttp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.google.gson.Gson;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.FormBody;
import okhttp3.HttpUrl;
import okhttp3.Interceptor;
import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.ResponseBody;
import okhttp3.logging.HttpLoggingInterceptor;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initokhttp();
        Button btnGet = findViewById(R.id.btn_test_get);
        btnGet.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                testget();
            }
        });
        Button btnPost = findViewById(R.id.btn_test_post);
        btnPost.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                testpost2();
            }
        });
    }
    public class HttpLogger implements HttpLoggingInterceptor.Logger{
        @Override
        public void log(String message) {
            Log.i("logokhttp", message);
        }
    }
    private OkHttpClient client;
    public void initokhttp(){
        HttpLoggingInterceptor httpLoggingInterceptor = new HttpLoggingInterceptor(new HttpLogger());
        httpLoggingInterceptor.setLevel(HttpLoggingInterceptor.Level.BODY);
        client = new OkHttpClient.Builder()
                .addNetworkInterceptor(httpLoggingInterceptor)
                .build();
    }
    public void testget(){
        Request.Builder requestBuilder = new Request.Builder();
        HttpUrl.Builder urlBuilder = HttpUrl.parse("http://httpbin.org/get").newBuilder();
        urlBuilder.addQueryParameter("show_env", "11");
        requestBuilder.url(urlBuilder.build());
        Request request = requestBuilder.build();
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {

            }

            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                if (response.isSuccessful()){
                    ResponseBody body = response.body();
                    String s = body.string();
                    //Log.i("test", s);
                }
            }
        });
    }

    public class UserInfo{
        String userid;
        String token;
    }

    public void testpost(){
        RequestBody requestBody = new FormBody.Builder()
                .add("userid", "1234")
                .add("token", "abcd")
                .build();
        Request request = new Request.Builder()
                .url("http://httpbin.org/anything")
                .post(requestBody)
                .build();
        client.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {

            }

            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                if (response.isSuccessful()){
                    ResponseBody body = response.body();
                    String s = body.string();
                    //Log.i("test", s);
                }
            }
        });
    }

    public void testpost2(){
        UserInfo userInfo = new UserInfo();
        userInfo.userid = "1234";
        userInfo.token = "abcd";
        Gson gson = new Gson();
        String json = gson.toJson(userInfo);
        MediaType JSON = MediaType.parse("application/json; charset=utf-8");
        RequestBody requestBody = RequestBody.create(JSON, json);
        final Request request = new Request.Builder()
                .url("http://httpbin.org/anything")
                .post(requestBody)
                .build();
//        new Thread(new Runnable() {
//            @Override
//            public void run() {
//                try{
//                    Response response = client.newCall(request).execute();
//                   //Log.i("TAG", response.body().string());
//                }catch (IOException e){
//                    e.printStackTrace();
//                }
//            }
//        }).start();

        client.newCall(request).enqueue(new Callback(){
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                Log.i("failed", "failed");
            }

            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                if (response.isSuccessful()){
                    ResponseBody body = response.body();
                    String s = body.string();
                    //Log.i("test", s);
                }
            }
        });
    }
}
