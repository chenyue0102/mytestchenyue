<template>
    <div>{{text}}</div>
    <button @click="onClick">click</button>
</template>
<script setup>
import { ReactiveEffect, getCurrentInstance } from 'vue'
const {appContext} = getCurrentInstance()
const name = "Footer"
const props = defineProps({
    text:Text
})
const eventBus = appContext.config.globalProperties.$bus
eventBus.on('onFooterText', (val)=>{
    props.text = val
})
const onClick = ()=>{
    eventBus.emit('onHeaderText', "change text")
}
</script>