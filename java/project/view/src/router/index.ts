import {createRouter, createWebHistory} from 'vue-router'
const router = createRouter({
    //使用createWebHistory，去掉url中井号
    history:createWebHistory(process.env.BASE_URL),//createWebHashHistory(),
    routes:[
        {
            path:'/',
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