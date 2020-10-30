#include "ShareData.h"
#include <assert.h>

ShareData & ShareData::instance() {
    static ShareData ins;
    return ins;
}

ShareData::ShareData() : mJavaVM(nullptr){

}

void ShareData::setJavaVM(JavaVM *javaVm) {
    std::lock_guard<std::mutex> lk(mMutex);
    mJavaVM = javaVm;
}

JavaVM *ShareData::getJavaVM() {
    std::lock_guard<std::mutex> lk(mMutex);
    assert(nullptr != mJavaVM);
    return mJavaVM;
}

template<typename T>
bool insertObject(std::map<jlong, T*> &mp, jlong id, T *item){
    auto iter = mp.find(id);
    if (iter == mp.end()){
        mp.insert(std::make_pair(id, item));
        return true;
    }else{
        assert(false);
        return false;
    }
}

bool ShareData::insertSpineItem(jlong id, SpineItem *spineItem) {
    std::lock_guard<std::mutex> lk(mMutex);
    return insertObject(mSpineItems, id, spineItem);
}

template<typename T>
T* removeObject(std::map<jlong, T*> &mp, jlong id){
    auto iter = mp.find(id);
    if (iter != mp.end()){
        T *item = iter->second;
        mp.erase(iter);
        return item;
    }else{
        assert(false);
        return nullptr;
    }
}

SpineItem *ShareData::removeSpineItem(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return removeObject(mSpineItems, id);
}

template<typename T>
T* getObject(std::map<jlong, T*> &mp, jlong id){
    auto iter = mp.find(id);
    if (iter != mp.end()){
        return iter->second;
    }else{
        assert(false);
        return nullptr;
    }
}

SpineItem *ShareData::getSpineItem(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return getObject(mSpineItems, id);
}

bool ShareData::insertRenderCmdsCache(jlong id, RenderCmdsCache *renderCmdsCache) {
    std::lock_guard<std::mutex> lk(mMutex);
    return insertObject(mRenderCmdsCaches, id, renderCmdsCache);
}

RenderCmdsCache *ShareData::removeRenderCmdsCache(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return removeObject(mRenderCmdsCaches, id);
}

RenderCmdsCache *ShareData::getRenderCmdsCache(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return getObject(mRenderCmdsCaches, id);
}

bool ShareData::insertTextureLoader(jlong id, AimyTextureLoader *loader) {
    std::lock_guard<std::mutex> lk(mMutex);
    return insertObject(mTextuerLoaders, id, loader);
}

AimyTextureLoader *ShareData::removeTextureLoader(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return removeObject(mTextuerLoaders, id);
}

AimyTextureLoader *ShareData::getTextureLoader(jlong id) {
    std::lock_guard<std::mutex> lk(mMutex);
    return getObject(mTextuerLoaders, id);
}
