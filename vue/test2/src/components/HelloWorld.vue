<script setup>
import { ref } from 'vue'

defineProps({
  msg: String,
})

const count = ref(0)
const spantext = "mytest_spantext"
const htmlcode = "<p>test</p>"
const oncetest = "once text"
function change(){
  count.value++
}

</script>

<template>
  <h1>{{ msg }}</h1>

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
    <span>{{oncetest}}</span>
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
