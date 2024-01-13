import {createRouter, createWebHistory} from 'vue-router'
const router = createRouter({
    //使用createWebHistory，去掉url中井号
    history:createWebHistory(
        import.meta.env.VITE_PREFIX_URL
        ),//createWebHashHistory(),
    routes:[
        {
            path:'/',
            name:"root",
            component:()=>import('../components/MainPage.vue')
        },
        {
            path:'/home',
            name:"home",
            component:()=>import('../components/MainPage.vue')
        },
        {
            path:'/helloworld',
            name:'helloworld',
            component:()=>import('../components/HelloWorld.vue')
        },
        {
            path:'/login',
            name:"login",
            component:()=>import('../components/LoginPage.vue')
        }
    ]
})
export default router