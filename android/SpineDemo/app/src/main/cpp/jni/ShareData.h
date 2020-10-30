#ifndef Share_Data_h_
#define Share_Data_h_
#include <map>
#include <mutex>
#include <jni.h>

class SpineItem;
class RenderCmdsCache;
class AimyTextureLoader;
class ShareData{
public:
    static ShareData& instance();

public:
    ShareData();

public:
    void setJavaVM(JavaVM *javaVm);
    JavaVM* getJavaVM();

public:
    bool insertSpineItem(jlong id, SpineItem *spineItem);
    SpineItem* removeSpineItem(jlong id);
    SpineItem* getSpineItem(jlong id);

    bool insertRenderCmdsCache(jlong id, RenderCmdsCache *renderCmdsCache);
    RenderCmdsCache* removeRenderCmdsCache(jlong id);
    RenderCmdsCache* getRenderCmdsCache(jlong id);

    bool insertTextureLoader(jlong id, AimyTextureLoader *loader);
    AimyTextureLoader* removeTextureLoader(jlong id);
    AimyTextureLoader* getTextureLoader(jlong id);

private:
    std::mutex mMutex;
    JavaVM *mJavaVM;
    std::map<jlong, SpineItem*> mSpineItems;
    std::map<jlong, RenderCmdsCache*> mRenderCmdsCaches;
    std::map<jlong , AimyTextureLoader*> mTextuerLoaders;
};

#endif