import axios from 'axios'
import store from '../state'
import constants from './constants';

axios.defaults.headers['Content-Type'] = 'application/json;charset=utf-8';
const service = axios.create({
    baseURL:constants.BASE_URL,
    timeout:10000
})

function refreshToken(){
    const refreshToken = store.state.refreshToken;
    console.log(refreshToken)
    var req = {
        refreshToken:refreshToken
    }
    const str = JSON.stringify(req);
    console.log(str)
    return service.post('/refreshtoken', str).then(res => res.data)
}

service.interceptors.response.use((response : any) =>{
    const code = response.data.code;
    if (code == -3){//access token 过期
        return refreshToken().then(res =>{
            const newAccessToken = res.data.accessToken;
            console.log("newAccessToken:" + newAccessToken)
            service.defaults.headers['token'] = newAccessToken;
            console.log("setToken")
            const config = response.config;
            config.headers['token'] = newAccessToken;
            store.commit('updateToken', [newAccessToken, store.state.refreshToken])
            console.log("commit")
            console.log("baseURL" + config.baseURL)
            //config.baseURL = ''
            return service(config)
        }).catch((_res : any) =>{
            //调到登陆
            store.commit('updateToken', ['',''])
            window.location.href = '/login'
        })
    }
    return response;
},error =>{
    store.commit('updateToken', ['',''])
    return Promise.reject(error)
})

export default service