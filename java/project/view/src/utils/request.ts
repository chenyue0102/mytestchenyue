import axios from 'axios'

axios.defaults.headers['Content-Type'] = 'application/json;charset=utf-8';
const service = axios.create({
    baseURL:'http://localhost:8080/observe',
    timeout:10000
})

export default service