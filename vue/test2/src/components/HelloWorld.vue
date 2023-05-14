<script setup>
import { reactive, ref } from 'vue'
import Child from './Child.vue'

defineProps({
  msg: String,
})

const count = ref(0)
const spantext = "mytest_spantext"
const htmlcode = "<p>test</p>"
var oncetest = "once text"
const state = reactive({
  fe:'vue',
  farray:[],
  modeltext:"abc",
  isRed:false,
  color:'red',
  fontsize:''
})
function change(){
  count.value++
  oncetest = 'once text2'
  state.isRed = !state.isRed
  state.color = 'blue'
  state.fontsize = 'big'
}
function padd(num){
  count.value += num
}
</script>

<template>
  <!--子控件-->
  <Child :count="count" @add="padd"></Child>
  <h1>{{ msg }}</h1>

  <select name="fe" v-model="state.fe">
    <option value="react">react</option>
    <option value="vue">vue</option>
    <option value="test">test</option>
  </select>
  <input type="radio" v-model="state.fe" value="react"/>
  <input type="radio" v-model="state.fe" value="vue"/>
  <input type="radio" v-model="state.fe" value="test">
  <p>{{state.fe}}</p>
  <div>
    <label>react</label>
    <input type="checkbox" v-model="state.farray" value="react"/>
  </div>
  <div>
    <label>vue</label>
    <input type="checkbox" v-model="state.farray" value="vue" />
  </div>
  <div>
    <label>test</label>
    <input type="checkbox" v-model="state.farray" value="test" />
  </div>
  <p>{{state.farray}}</p>
  <p v-if="state.fe == 'react'">react selected</p>
  <p v-else-if="state.fe == 'vue'">vue selected</p>
  <p v-else>test selected</p>
  <p v-show="state.fe == 'vue'">vue show</p>
  <div v-for="(item, index) in state.farray" :key="index">
    <p>item: {{item}}</p>
  </div>
  <div v-bind:class="{color:state.isRed}">red </div>
  <div v-bind:class="[state.color,state.fontsize]">blue</div>
  <div class="card">
    <button type="button" @click="change">count is {{ count }}</button>
    <p>
      Edit
      <code>components/HelloWorld.vue</code> to test HMR
    </p>
    <span>{{spantext}}</span>
    <p/>
    <span v-text="spantext" ></span>
    <p/>
    <!--更新inner html-->
    <div v-html="htmlcode" ></div>
    <!--只渲染一次-->
    <span v-once>{{oncetest}}</span>
    <p/>
    <input type="text"  v-bind:value="oncetest" >
    <p/>
    <input type="text" v-model.lazy="state.modeltext">
    <!--<input :value="modeltext" @input="modeltext=e.detail.value"/>-->
    <br/>
    <p>{{ state.modeltext }}</p>
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
.color{
  background-color: red;
}
.blue{
  color: blue;
}
.big{
  font-size: 20px;
}
</style>
