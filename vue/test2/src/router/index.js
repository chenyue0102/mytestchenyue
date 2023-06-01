import {createRouter, createWebHashHistory} from 'vue-router'
const router = createRouter({
    history:createWebHashHistory(),
    routes:[
        {
            path:'/',
            name:'home',
            component:()=>import('../components/Home.vue')
        },
        {
            path:'/about',
            name:"aboue",
            component:()=>import('../components/About.vue')
        }
    ]
})
export default router