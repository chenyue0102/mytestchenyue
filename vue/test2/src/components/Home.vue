<template>
    <div>~home~</div>
    <button @click="goTo">goto about</button>
</template>
<script setup>
import router from "../router"
const name = "Home"

const goTo = ()=>{
    router.push({path:'/about', query:{msg:"hello"}})
}

</script>