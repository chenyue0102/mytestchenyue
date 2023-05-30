<script setup>
import {computed, getCurrentInstance, reactive, readonly, ref, watchEffect, watch} from 'vue'
import GrandSon from './GrandSon.vue'
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
    console.log("emit add")
    ctx.emit('add', 10)
}
const state = reactive({
    text:"test",
    num:1
})
let emit = defineEmits(["add"])
const text2 = ref('test')
setTimeout(()=>{
    //alert('对不起, 要你久候')
    console.log("timeout")
    state.text = 'demos'
    text2.value = 'demo2'
    //state_readonly.name = "new name"
}, 2000)
setTimeout(()=>{
    state.num = 2
}, 3000)
const state_readonly = readonly({
    name:'name readonly'
})
watchEffect(()=>{
    console.log('watchEffect:' + state.text)
})
watch(()=>{
    return state.num
},(nextData, preData)=>{
    console.log("pre:" + preData + " next:" + nextData)
})
</script>
<template>
    <GrandSon>~GrandSon~</GrandSon>
    <p>count:{{count}}</p>
    <p>count2:{{count2}}</p>
    <p>text:{{state.text}} text2:{{text2}}</p>
    <p>readonly:{{state_readonly.name}}</p>
    <button @click="addNum">+</button>
</template>
<style scoped>
</style>