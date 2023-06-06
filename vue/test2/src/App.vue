<template>
    <div class="container">
        <router-link to="/">Home</router-link>
        <br>
        <!--replace 历史记录不会留下记录-->
        <router-link :to="{path:'/about', query:{msg:'hello, about'}}" replace>About</router-link>
    </div>
    <router-view />
</template>
<script setup>
import { ref } from "vue"
const name = "App"
</script>