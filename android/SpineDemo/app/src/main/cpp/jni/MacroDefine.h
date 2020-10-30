//
// Created by EDZ on 2020/10/29.
//

#ifndef SPINEDEMO_MACRODEFINE_H
#define SPINEDEMO_MACRODEFINE_H

#define GETRENDER(swig_cptr) \
RenderCmdsCache *renderCmdsCache = ShareData::instance().getRenderCmdsCache(swig_cptr); \
if (nullptr == renderCmdsCache){ \
    Log::e("get render failed fun:%s line:%d", __FUNCTION__, __LINE__); \
    assert(false); \
    throw ; \
}

#define GETSKELETON(swig_cptr) \
SpineItem *spineItem = ShareData::instance().getSpineItem(swig_cptr); \
if (nullptr == spineItem){ \
    Log::e("get spine failed fun:%s line:%d", __FUNCTION__, __LINE__); \
    assert(false); \
    throw ; \
} \
spine::Skeleton *skeleton = spineItem->getSkeleton(); \
if (nullptr == skeleton){ \
    Log::e("get skeleton failed fun:%s line:%d", __FUNCTION__, __LINE__); \
    assert(false); \
    throw ; \
}

#define GETSPINEITEM(swig_cptr) \
SpineItem *spineItem = ShareData::instance().getSpineItem(swig_cptr); \
if (nullptr == spineItem){ \
    Log::e("get spine failed fun:%s line:%d", __FUNCTION__, __LINE__); \
    assert(false); \
    throw ; \
}

#define GETTEXTURELOADER(swig_cptr) \
AimyTextureLoader *textureLoader = ShareData::instance().getTextureLoader(swig_cptr); \
if (nullptr == textureLoader){ \
    Log::e("get texture loader failed fun:%s line:%d", __FUNCTION__, __LINE__); \
    assert(false); \
    throw ; \
}

#endif //SPINEDEMO_MACRODEFINE_H
