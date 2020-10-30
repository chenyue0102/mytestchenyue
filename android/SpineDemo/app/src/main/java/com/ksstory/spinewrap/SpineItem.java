package com.ksstory.spinewrap;

/**
 * 只能够在主线程访问
 */
public class SpineItem extends BaseWrap{
    public SpineItem(){
        super(SpineItemJNI.new_SpineItem(), true);
    }

    public void setAtlasFile(String filePath){
        SpineItemJNI.setAtlasFile(swigCPtr, filePath);
    }

    public void setSkeletonFile(String filePath){
        SpineItemJNI.setSkeletonFile(swigCPtr, filePath);
    }

    public boolean create(TextureLoader textureLoader){
        long id = textureLoader.getId();
        return SpineItemJNI.create(swigCPtr, id);
    }

    public void setAnimation(int trackIndex, String name, boolean loop){
        SpineItemJNI.setAnimation(swigCPtr, trackIndex, name, loop);
    }

    public Skeleton getSkeleton(){
        long id = SpineItemJNI.getSkeleton(swigCPtr);
        return new Skeleton(id);
    }

    public void updateSkeletonAnimation(float delta){
        SpineItemJNI.updateSkeletonAnimation(swigCPtr, delta);
    }

    //此函数，只能够BatchRenderHelper调用
    protected void renderToCache(RenderCmdsCache renderCmdsCache){
        SpineItemJNI.renderToCache(swigCPtr, renderCmdsCache.getId());
    }

    @Override
    protected void onDeleteJNI(long swigCPtr) {
        SpineItemJNI.delete_SpineItem(swigCPtr);
    }
}
