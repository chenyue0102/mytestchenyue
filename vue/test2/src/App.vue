<script setup>
import {ref} from 'vue'
import HelloWorld from './components/HelloWorld.vue'
import Header from './components/Header.vue'
import Footer from './components/Footer.vue'
const current = ref('Header')
const props = ref({text:'abc123'})
const my_callback = (msg)=>{
  props.value = {text:'weerw'}
}
const change = (name)=>{
  current.value = name
  if (name == 'Header'){
    alert('callback' + name)
    props.value={text:'def321'}
  }
}
</script>

<template>
  <div>
    <component :is="current" v-bind="props" @setText="my_callback"></component>
    <button @click="change('Header')">变成Header</button>
    <button @click="change('Footer')">变成Footer</button>
    <Header text="abc"/>
    <a href="https://vitejs.dev" target="_blank">
      <img src="/vite.svg" class="logo" alt="Vite logo" />
    </a>
    <a href="https://vuejs.org/" target="_blank">
      <img src="./assets/vue.svg" class="logo vue" alt="Vue logo" />
    </a>
  </div>
  <HelloWorld msg="Vite + Vue" />
  <Footer />
</template>
<style scoped>
.logo {
  height: 6em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}
.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}
.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}
</style>
