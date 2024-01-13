<template>
    <div>
        <label>对方用户id:</label>
        <input type="text" placeholder="对方用户id" v-model="state.userId" class="input_style" />
        <button type="primary" @click="connectWebSocket" class="login_style">连接WebSocket</button>
        <button type="primary" @click="sendWebSocketMsg" class="login_style">发送WebSocket消息</button>
    </div>
    
</template>
<script setup>
import {reactive, ref} from 'vue'
import {initWebSocket} from '../utils/websockethelper'

const state = reactive({
    userId:0,
})
async function sendWebSocketMsg(){

}
function connectWebSocket(){
    initWebSocket();
}
</script>
<style scoped>
.input_style{
    width:200px;
    margin: 0 auto 10px auto;
    height: 30px;
}
</style>