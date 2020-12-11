//
// Created by EDZ on 2020/12/11.
//

#ifndef TESTSURFACE_IMAGEREADERHELPER_H
#define TESTSURFACE_IMAGEREADERHELPER_H
#include <media/NdkImageReader.h>

class ImageReaderHelper {
public:
    struct ImageData{
        int32_t pixelStride;
        int32_t rowStride;
        uint8_t *data;
        int dataLength;
    };
public:
    ImageReaderHelper();
    ~ImageReaderHelper();

public:
    void setFormat(int format);
    void setSize(int width, int height);

public:
    media_status_t create();
    void destroy();
    ANativeWindow* getNativeWindow()const;

private:
    static void AImageReader_ImageCallback(void* context, AImageReader* reader);

protected:
    virtual void onImageCallback(int format, int32_t width, int32_t height, ImageData *images, int imageCount);

private:
    AImageReader_ImageListener mImageListener;
    AImageReader *mAImageReader;
    ANativeWindow *mANativeWindow;
    int mFormat;
    int mWidth, mHeight;
};


#endif //TESTSURFACE_IMAGEREADERHELPER_H
