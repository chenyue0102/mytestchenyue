<template>
    <div class="login">
        <div>
            <h3 class="login_label" >登陆</h3>
        </div>
        <div>
            <input type="text" placeholder="请输入用户名" v-model="state.loginName" clearable class="input_style" />
            
        </div>
        <div>
            <input type="password" placeholder="请输入密码" v-model="state.loginPassword" show-password class="input_style" />
        </div>
        <div class="outerbox">
            <input type="text" placeholder="验证码" v-model="state.verifyCode" class="verify_style" />
            <img :src="state.verifyCodeUrl" @click="getCode" class="verify_img_style"/>
        </div>
        <div>
            <button type="primary" @click="login" class="login_style">登陆</button>
        </div>
        <p>{{state.loginName}}</p>
    </div>
</template>
<script setup>
import { provide, reactive, ref } from 'vue'
import {v4 as uuidv4} from 'uuid'
import request from '../utils/request'
import store from '../state'
import router from "../router"

defineProps({
  msg: String,
})

const state = reactive({
    loginName:"",
    loginPassword:"",
    verifyCode:"",
    uuid:""
})
function hex2a(arr){
    var result = '';
    for (var i = 0; i < arr.length; i++){
        var str = arr[i].toString(16);
        str = str.length == 0 ? "00" : 
            str.length == 1 ? "0" + str :
            str.length == 2 ? str : str.substring(str.length - 2, str.length);
        result += str;
    }
    return result;
}
function buf2hex(buffer) { // buffer is an ArrayBuffer
    return Array.prototype.map.call(new Uint8Array(buffer), x => ('00' + x.toString(16)).slice(-2)).join('');
}
function buf2Base64(buffer) {
    return btoa(String.fromCharCode.apply(null, new Uint8Array(buffer)));
}
async function login(){
    let res = await request({
        url:'/random',
        method:'get'
    });
    let serviceRandom = res.data.data.serviceRandom;
    let clientRandom = uuidv4();
    let password = state.loginPassword + serviceRandom + clientRandom;
    //console.log(password)
    //alert(serviceRandom);
    const encoder = new TextEncoder();
    let dt = encoder.encode(password);
    let hash = await crypto.subtle.digest('SHA-256', dt);
    //alert(hash)
    //console.log(typeof(hash))
    let strPasswordHash = buf2hex(hash)
    //alert(strPasswordHash)
    //console.log(s)
    var loginRequest = {
        "loginName":state.loginName,
        "passwordHash":strPasswordHash,
        "serverRandom":serviceRandom,
        "clientRandom":clientRandom,
        "verifyCode":state.verifyCode,
        "verifyCodeUUID":state.uuid
    }
    let str = JSON.stringify(loginRequest);
    //console.log(str)
    let res2 = await request({
        url:'/login',
        method:'post',
        data:str
    });
    let errorCode = res2.data.code;
    let msg = res2.data.msg;
    if (0 != errorCode){
        alert(msg);
        return;
    }
    let accessToken = res2.data.data.accessToken;
    let refreshToken = res2.data.data.refreshToken;
    //let s = JSON.stringify(res2);
    console.log(accessToken + " " + refreshToken)  
    //alert("goto helloworld")
    store.commit('updateToken', [accessToken, refreshToken])
    
    router.push({path:'/', query:{msg:"helloworld"}})
}
function getCodeImg(){
    return request({
        url:'/verifycode',
        method:'get'
    })
}

function getCode(){
    getCodeImg().then(res => {
        state.verifyCodeUrl = res.data.img
        state.uuid = res.data.uuid
    })
}
getCode()
</script>
<style scoped>
.login{
    background-color: lightgray;
    width: 400px;
    height: 400px;
}
.login_label{
    font-size: 50px;
    color:lightseagreen;
    padding-top: 20px;
    padding-bottom: 0px;
}

.input_style{
    width:200px;
    margin: 0 auto 10px auto;
    height: 30px;
}
.outerbox{
    width:200px;
    margin: 0px auto 10px auto;
    display: flex;
    flex-flow: row nowrap;
    justify-content: space-between;
    align-content: flex-start;
}
.verify_style{
    width:50px;
    height: 36px;
    vertical-align: bottom;
    margin-right: 10px;
    
}
.verify_img_style{
    vertical-align: bottom;
}
.el-input > input{
    height: 100px;
}
.login_style{
    width:200px;
}
</style>