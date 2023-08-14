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
function login(){
    request({
        url:'/random',
        method:'get'
    }).then(res =>{
        let serviceRandom = res.data.data.serviceRandom;
        let clientRandom = uuidv4();
        let password = state.password + serviceRandom + clientRandom;
        //alert(password)
        const encoder = new TextEncoder();
        let passwordHash = encoder.encode(password);
        let strPasswordHash = hex2a(passwordHash)
        //console.log(s)
        var loginRequest = {
            "loginName":state.loginName,
            "passwordHash":strPasswordHash,
            "serverRandom":serviceRandom,
            "clientRandom":clientRandom,
            "verifyCode":state.verifyCode,
            "verifyCodeUUID":state.verifyCodeUUID
        }
        let str = JSON.stringify(loginRequest);
        console.log(str)
        request({
            url:'login',
            method:'get'
        }).then(res =>{
            let s = JSON.stringify(res);
            console.log(s)
        });
    })
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