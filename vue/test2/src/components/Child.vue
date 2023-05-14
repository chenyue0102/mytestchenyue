<script setup>
import {computed, getCurrentInstance, reactive, readonly, ref} from 'vue'
const name="Child"
const ctx = getCurrentInstance()
const props = defineProps({
    count:Number,
    add:Function,
})
const count2 = computed(()=>{
    return props.count + 1
})
const addNum = ()=>{
    ctx.emit('add', 10)
}
const state = reactive({
    text:"test"
})
const text2 = ref('test')
setTimeout(()=>{
    //alert('对不起, 要你久候')
    state.text = 'demos'
    text2.value = 'demo2'
    console.log("timeout")
    state_readonly.name = "new name"
}, 2000)
const state_readonly = readonly({
    name:'name readonly'
})
</script>
<template>
    <p>count:{{count}}</p>
    <p>count2:{{count2}}</p>
    <p>text:{{state.text}} text2:{{text2}}</p>
    <p>readonly:{{state_readonly.name}}</p>
    <button @click="addNum">+</button>
</template>
<style scoped>
</style>