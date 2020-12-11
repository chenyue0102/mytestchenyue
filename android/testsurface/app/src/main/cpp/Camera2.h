//
// Created by EDZ on 2020/12/10.
//

#ifndef TESTSURFACE_CAMERA2_H
#define TESTSURFACE_CAMERA2_H
#include <functional>
#include <map>
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <media/NdkImageReader.h>
#include "StructDefine.h"

class Camera2 {
public:
    Camera2();
    ~Camera2();

public:
    static bool isSupportCamera2();
    static CameraConfig getCameraConfig();

public:
    void setCameraSize(int width, int height);

public:
    camera_status_t openCamera(const char* cameraId);
    camera_status_t addSurface(ACameraDevice_request_template templateId, ANativeWindow *nativeWindow);
    camera_status_t start();
    camera_status_t stop();
    void removeAllSurface();
    void closeCamera();

public://ACameraDevice_StateCallbacks
    static void ACameraDevice_StateCallback(void* context, ACameraDevice* device);
    static void ACameraDevice_ErrorStateCallback(void* context, ACameraDevice* device, int error);

private:
    void ACameraDevice_StateCallback(ACameraDevice* device);
    void ACameraDevice_ErrorStateCallback(ACameraDevice* device, int error);

private:
    static void ACameraCaptureSession_stateCallback_onReady(void* context, ACameraCaptureSession *session);
    static void ACameraCaptureSession_stateCallback_onActive(void* context, ACameraCaptureSession *session);
    static void ACameraCaptureSession_stateCallback_onClosed(void* context, ACameraCaptureSession *session);

private:
    void ACameraCaptureSession_stateCallback_onReady(ACameraCaptureSession *session);
    void ACameraCaptureSession_stateCallback_onActive(ACameraCaptureSession *session);
    void ACameraCaptureSession_stateCallback_onClosed(ACameraCaptureSession *session);

private:
    static void forEachMetaData(std::function<bool(const char *deviceId, const ACameraMetadata_const_entry&)> fun);

private:
    ACameraDevice_StateCallbacks mDeviceStateCallbacks;
    ACameraCaptureSession_stateCallbacks mSessionStateCallbacks;
    ACameraDevice *mACameraDevice;
    //ACaptureRequest *mACaptureRequest;
    ACaptureSessionOutputContainer *mACaptureSessionOutputContainer;
    ACameraCaptureSession *mACameraCaptureSession;

    struct CaptureRequest{
        ACaptureRequest *captureRequest;
        std::vector<ACameraOutputTarget*> targets;
    };
    std::map<ACameraDevice_request_template, CaptureRequest> mACaptureRequests;
    std::vector<ACaptureSessionOutput*> mACaptureSessionOutputs;
    CameraSize mSize;
};


#endif //TESTSURFACE_CAMERA2_H
