import { createApp } from 'vue'
import './style.css'
import mitt from 'mitt'
import App from './App.vue'
//import App from './AppRoute.vue'
import Header from './components/Header.vue'
import Footer from './components/Footer.vue'
import router from './router'
import store from './state'

router.beforeEach((to, from)=>{
    console.log("to:" + to.name + " from" + from.name)
    let accessToken = localStorage.getItem('accessToken');
    let refreshToken = localStorage.getItem('refreshToken')
    if (refreshToken == null){
        refreshToken = 'new refresh token';
    }else{
        refreshToken = 'old refresh token';
    }
    accessToken = 'access token'
    store.commit('updateToken', [accessToken, refreshToken])
    let msg = "accessToken:"+store.state.accessToken + " refreshToken:" + store.state.refreshToken
    console.log(msg);
    localStorage.setItem("accessToken", accessToken);
    localStorage.setItem('refreshToken', refreshToken);
    alert(msg)
})
const app = createApp(App)
//app.config.globalProperties.$bus = new mitt()
//app.component('Header', Header)
//app.component('Footer', Footer)
app.use(router)
app.mount('#app')
