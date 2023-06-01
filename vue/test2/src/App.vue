<template>
    <div class="container">
        <router-link to="/">Home</router-link>
        <br>
        <router-link to="about">About</router-link>
    </div>
    <router-view />
</template>
<script setup>
import { ref } from "vue"
const name = "App"
</script>