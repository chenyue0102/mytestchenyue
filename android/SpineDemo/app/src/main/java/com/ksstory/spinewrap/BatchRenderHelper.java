package com.ksstory.spinewrap;

import java.util.ArrayList;

/**
 *
 */
public class BatchRenderHelper {

    /**
     * 将所有动画绘制到缓存中
     * @param items
     * @param renderCmdsCache
     */
    public static void batchRender(ArrayList<SpineItem> items, RenderCmdsCache renderCmdsCache){
        renderCmdsCache.clearCache();
        for (SpineItem item : items){
            item.renderToCache(renderCmdsCache);
        }
        renderCmdsCache.setDirty();
    }
}
