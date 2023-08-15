import  Vuex from 'vuex'
import createPersistedState  from 'vuex-persistedstate'

export default new Vuex.Store({
    plugins:[createPersistedState()],
    state:{
        accessToken:'',
        refreshToken:''
    },
    mutations:{
        updateToken(state, [accessToken, refreshToken]){
            state.accessToken = accessToken;
            state.refreshToken = refreshToken;
        }
    }
})