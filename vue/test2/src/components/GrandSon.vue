<template>
    <div>grand son {{sonName}}</div>
</template>
<script setup>
import {inject} from 'vue'
const sonName = inject('sonName', 'sonName')
const name = 'GrandSon'
</script>