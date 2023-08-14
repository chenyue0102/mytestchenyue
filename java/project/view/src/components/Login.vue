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
            <button type="primary" @click="getCode" class="login_style">登陆</button>
        </div>
        <p>{{state.loginName}}</p>
    </div>
</template>
<script setup>
import { provide, reactive, ref } from 'vue'
import request from '../utils/request'

const state = reactive({
    loginName:"",
    loginPassword:"",
    verifyCode:"",
    uuid:""
})
function login(){
    alert("login");
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