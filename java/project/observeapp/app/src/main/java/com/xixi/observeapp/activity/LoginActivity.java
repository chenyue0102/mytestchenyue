package com.xixi.observeapp.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.util.Base64;
import android.util.Log;
import android.widget.EditText;
import android.widget.ImageView;

import com.google.gson.Gson;
import com.xixi.observeapp.R;
import com.xixi.observeapp.bean.LoginRequest;
import com.xixi.observeapp.bean.LoginResult;
import com.xixi.observeapp.bean.Result;
import com.xixi.observeapp.bean.ServiceRandomResult;
import com.xixi.observeapp.bean.VerifyCodeResult;
import com.xixi.observeapp.network.ApiManager;
import com.xixi.observeapp.constants.Constants;
import com.xixi.observeapp.network.ObserveService;
import com.xixi.observeapp.network.WebSocketClient;
import com.xixi.observeapp.util.SpUtils;
import com.xixi.observeapp.util.StringUtil;

import java.security.MessageDigest;
import java.util.UUID;

import io.reactivex.Observer;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;
import okhttp3.MediaType;
import okhttp3.RequestBody;

public class LoginActivity extends AppCompatActivity {
    private static final String TAG = "LoginActivity";
    EditText mServerAddress;
    EditText mLoginName;
    EditText mPassword;
    EditText mEditVerifyCode;
    ImageView mVerifyCode;

    String mUUID;

    ObserveService observeService;

    Gson mGson = new Gson();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_activify);

        mServerAddress = findViewById(R.id.et_server_address);
        mLoginName = findViewById(R.id.et_login_name);
        mPassword = findViewById(R.id.et_password);
        mVerifyCode = findViewById(R.id.iv_verify_code);
        mEditVerifyCode = findViewById(R.id.et_verify_code);

        observeService = ApiManager.getInstance().getProxy(ObserveService.class);

        findViewById(R.id.btn_close).setOnClickListener(v->this.onBackPressed());
        findViewById(R.id.btn_login).setOnClickListener(v->onLogin());
        getVerifyCode();
    }

    private void getVerifyCode(){
        observeService.getVerifyCode()
                .subscribeOn(Schedulers.newThread())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<Result<VerifyCodeResult>>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(Result<VerifyCodeResult> value) {
                        mUUID = value.getData().getUuid();
                        Log.w(TAG, value.getData().getUuid());
                        String base64 = value.getData().getImg();
                        byte[] decode = Base64.decode(base64.split(",")[1], Base64.DEFAULT);
                        Bitmap bitmap = BitmapFactory.decodeByteArray(decode, 0, decode.length);
                        mVerifyCode.setImageBitmap(bitmap);
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });
    }

    private void onLogin(){
        observeService.getServiceRandom()
                .subscribeOn(Schedulers.newThread())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<Result<ServiceRandomResult>>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(Result<ServiceRandomResult> value) {
                        try{
                            onGetServiceRandom(value.getData());
                        }catch (Exception e){
                            e.printStackTrace();
                        }
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });
    }
    private void onGetServiceRandom(ServiceRandomResult serviceRandomResult)throws Exception{
        String clientRandom = UUID.randomUUID().toString();
        LoginRequest request = new LoginRequest();
        request.setLoginName(mLoginName.getText().toString());
        String str = mPassword.getText().toString() + serviceRandomResult.getServiceRandom() + clientRandom;
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte []d= md.digest(str.getBytes());
        request.setPasswordHash(StringUtil.byteArrayToHex(d));
        request.setServerRandom(serviceRandomResult.getServiceRandom());
        request.setClientRandom(clientRandom);
        request.setVerifyCode(mEditVerifyCode.getText().toString());
        request.setVerifyCodeUUID(mUUID);
        String json = mGson.toJson(request);
        RequestBody requestBody = RequestBody.create(MediaType.parse(Constants.HeaderContentType), json);
        observeService.login(requestBody)
                .subscribeOn(Schedulers.newThread())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(new Observer<Result<LoginResult>>() {
                    @Override
                    public void onSubscribe(Disposable d) {

                    }

                    @Override
                    public void onNext(Result<LoginResult> value) {
                        LoginResult loginResult = value.getData();
                        SpUtils.putString(LoginActivity.this, Constants.ACCESS_TOKEN_NAME, loginResult.getAccessToken());
                        SpUtils.putString(LoginActivity.this, Constants.REFRESH_TOKEN_NAME, loginResult.getRefreshToken());
                        Log.w(TAG, loginResult.getAccessToken());

                        WebSocketClient.getInstance().init("ws://192.168.110.223:8080/observe/ws", loginResult.getAccessToken());
                    }

                    @Override
                    public void onError(Throwable e) {

                    }

                    @Override
                    public void onComplete() {

                    }
                });
    }
}