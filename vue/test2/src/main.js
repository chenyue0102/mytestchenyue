import { createApp } from 'vue'
import './style.css'
import mitt from 'mitt'
import App from './App.vue'
import Header from './components/Header.vue'
import Footer from './components/Footer.vue'


const app = createApp(App)
app.config.globalProperties.$bus = new mitt()
app.component('Header', Header)
app.component('Footer', Footer)
app.mount('#app')
