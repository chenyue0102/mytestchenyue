import { createApp } from 'vue'
import './style.css'
import mitt from 'mitt'
import App from './App.vue'
//import App from './AppRoute.vue'
import Header from './components/Header.vue'
import Footer from './components/Footer.vue'
import router from './router'

router.beforeEach((to, from)=>{
    console.log("to:" + to.name + " from" + from.name)
})
const app = createApp(App)
//app.config.globalProperties.$bus = new mitt()
//app.component('Header', Header)
//app.component('Footer', Footer)
app.use(router)
app.mount('#app')
