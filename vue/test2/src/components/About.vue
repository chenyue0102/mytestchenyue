<template>
    <div>~About~ {{query1}}</div>
</template>
<script setup>
import { useRoute } from "vue-router"

const name = "About"
const {query:query1}=useRoute()
</Script>