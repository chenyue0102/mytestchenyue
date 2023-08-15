<script setup lang="ts">
import { ref } from 'vue'
import store from '../state'
import request from '../utils/request'

defineProps({
  msg: String,
})

const count = ref(0)

async function uploadevent(){
  let timestamp = new Date().getTime();
  let eventRequest = {
    "eventId":1,
    "timestamp":timestamp,
    "data":2
  };
  let str = JSON.stringify(eventRequest);
  let res = await request({
    url:'/uploadevent',
    method:'post',
    headers:{
      'Content-Type':'application/json',
      'token':store.state.accessToken
    },
    data:str
  });

  console.log(res.data)
}
</script>

<template>
  <h1>{{ msg }}</h1>

  <h1>accessToken {{store.state.accessToken}}</h1>
  <div class="card">
    <button type="button" @click="count++">count is {{ count }}</button>
    <button type="button" @click="uploadevent">uploadevent</button>
    <p>
      Edit
      <code>components/HelloWorld.vue</code> to test HMR
    </p>
  </div>

  <p>
    Check out
    <a href="https://vuejs.org/guide/quick-start.html#local" target="_blank"
      >create-vue</a
    >, the official Vue + Vite starter
  </p>
  <p>
    Install
    <a href="https://github.com/vuejs/language-tools" target="_blank">Volar</a>
    in your IDE for a better DX
  </p>
  <p class="read-the-docs">Click on the Vite and Vue logos to learn more</p>
</template>

<style scoped>
.read-the-docs {
  color: #888;
}
</style>
