//
// Created by EDZ on 2020/12/11.
//

#include "ImageReaderHelper.h"
#include "Log.h"
#include "StructDefine.h"

#define MAX_IMAGES 2

ImageReaderHelper::ImageReaderHelper() : mAImageReader(nullptr), mANativeWindow(nullptr), mWidth(0), mHeight(0), mFormat(0){
    mImageListener.context = this;
    mImageListener.onImageAvailable = &ImageReaderHelper::AImageReader_ImageCallback;
}

ImageReaderHelper::~ImageReaderHelper() {
    destroy();
}

void ImageReaderHelper::setFormat(int format) {
    mFormat = format;
}

void ImageReaderHelper::setSize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

media_status_t ImageReaderHelper::create() {
    media_status_t mediaStatus = AMEDIA_ERROR_UNKNOWN;

    do {
        if (AMEDIA_OK != (mediaStatus = AImageReader_new(mWidth, mHeight, mFormat, MAX_IMAGES, &mAImageReader))){
            Log::e("ImageReaderHelper::create AImageReader_new %d failed", mediaStatus);
            assert(false);
            break;
        }
        if (AMEDIA_OK != (mediaStatus = AImageReader_setImageListener(mAImageReader, &mImageListener))){
            Log::e("ImageReaderHelper::create AImageReader_setImageListener %d failed", mediaStatus);
            assert(false);
            break;
        }
        if (AMEDIA_OK != (mediaStatus = AImageReader_getWindow(mAImageReader, &mANativeWindow))){
            Log::e("ImageReaderHelper::create AImageReader_getWindow %d failed", mediaStatus);
            assert(false);
            break;
        }
        mediaStatus = AMEDIA_OK;
    }while(false);
    if (AMEDIA_OK != mediaStatus){
        destroy();
    }
    return mediaStatus;
}

void ImageReaderHelper::destroy() {
    if (nullptr != mAImageReader){
        AImageReader_setImageListener(mAImageReader, nullptr);
        AImageReader_delete(mAImageReader);
    }
    mAImageReader = nullptr;
    mANativeWindow = nullptr;
}

ANativeWindow* ImageReaderHelper::getNativeWindow()const{
    assert(nullptr != mANativeWindow);
    return mANativeWindow;
}

void ImageReaderHelper::AImageReader_ImageCallback(void *context, AImageReader *reader) {
    ImageReaderHelper *pThis = reinterpret_cast<ImageReaderHelper*>(context);

    do {
        if (nullptr == pThis){
            assert(false);
            break;
        }
        AImage *tmpImage = nullptr;
        media_status_t mediaStatus = AMEDIA_ERROR_UNKNOWN;
        if (AMEDIA_OK != (mediaStatus = AImageReader_acquireLatestImage(reader, &tmpImage))){
            Log::e("ImageReaderHelper::AImageReader_ImageCallback AImageReader_acquireLatestImage %d failed", mediaStatus);
            assert(false);
            break;
        }
        std::unique_ptr<AImage, decltype(&AImage_delete)> image(tmpImage, &AImage_delete);
        int32_t format = 0;
        if (AMEDIA_OK != (mediaStatus = AImage_getFormat(image.get(), &format))){
            Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getFormat %d failed", mediaStatus);
            assert(false);
            break;
        }
        int32_t width = 0;
        if (AMEDIA_OK != (mediaStatus = AImage_getWidth(image.get(), &width))){
            Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getWidth %d failed", mediaStatus);
            assert(false);
            break;
        }
        int32_t height = 0;
        if (AMEDIA_OK != (mediaStatus = AImage_getHeight(image.get(), &height))){
            Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getHeight %d failed", mediaStatus);
            assert(false);
            break;
        }

        int32_t numPlanes = 0;
        if (AMEDIA_OK != (mediaStatus = AImage_getNumberOfPlanes(image.get(), &numPlanes))){
            Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getNumberOfPlanes %d failed", mediaStatus);
            assert(false);
            break;
        }

        std::vector<ImageReaderHelper::ImageData> imageDatas;
        for (int planeIdx = 0; planeIdx < numPlanes; planeIdx++){
            int32_t pixelStride = 0;
            if (AMEDIA_OK != (mediaStatus = AImage_getPlanePixelStride(image.get(), planeIdx, &pixelStride))){
                Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getPlanePixelStride %d failed", mediaStatus);
                assert(false);
                continue;
            }
            int32_t rowStride = 0;
            if (AMEDIA_OK != (mediaStatus = AImage_getPlaneRowStride(image.get(), planeIdx, &rowStride))){
                Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getPlaneRowStride %d failed", mediaStatus);
                assert(false);
                continue;
            }
            uint8_t *data = nullptr;
            int dataLength = 0;
            if (AMEDIA_OK != (mediaStatus = AImage_getPlaneData(image.get(), planeIdx, &data, &dataLength))){
                Log::e("ImageReaderHelper::AImageReader_ImageCallback AImage_getPlaneData %d failed", mediaStatus);
                assert(false);
                continue;
            }
            ImageReaderHelper::ImageData imageData;
            imageData.data = data;
            imageData.dataLength = dataLength;
            imageData.pixelStride = pixelStride;
            imageData.rowStride = rowStride;
            imageDatas.push_back(imageData);
        }
        pThis->onImageCallback(format, width, height, imageDatas.data(), imageDatas.size());
    }while (false);
}

void ImageReaderHelper::onImageCallback(int format, int32_t width, int32_t height, ImageReaderHelper::ImageData *images, int imageCount) {

}
