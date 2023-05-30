<template>
    <div>{{state.stext}} Header</div>
    <button @click="onClick">callback</button>
</template>
<script setup>
import {getCurrentInstance, reactive} from 'vue'
const name = 'Header'
const {appContext} = getCurrentInstance()
let emit = defineEmits(["setText"])
const labelText = props.text
const props = defineProps({
    text:Text,
    setText:Function,
})
const state = reactive({
    stext:props.text
})
const eventBus = appContext.config.globalProperties.$bus
eventBus.on('onHeaderText', (val)=>{
    //alert(val)
    state.stext = val
})
const onClick = ()=>{
    //alert("onClick")
    ctx.emit('setText', 'asfsdf')
}


</script>