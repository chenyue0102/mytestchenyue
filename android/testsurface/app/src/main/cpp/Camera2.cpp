//
// Created by EDZ on 2020/12/10.
//

#include "Camera2.h"
#include <assert.h>
#include <memory>
#include "Log.h"
#include "AndroidPlatform.h"



Camera2::Camera2() : mACameraDevice(nullptr),  mACaptureSessionOutputContainer(nullptr), mACameraCaptureSession(nullptr){
    mDeviceStateCallbacks.context = this;
    mDeviceStateCallbacks.onError = &Camera2::ACameraDevice_ErrorStateCallback;
    mDeviceStateCallbacks.onDisconnected = &Camera2::ACameraDevice_StateCallback;

    mSessionStateCallbacks.context = this;
    mSessionStateCallbacks.onClosed = &Camera2::ACameraCaptureSession_stateCallback_onClosed;
    mSessionStateCallbacks.onActive = &Camera2::ACameraCaptureSession_stateCallback_onActive;
    mSessionStateCallbacks.onReady = &Camera2::ACameraCaptureSession_stateCallback_onReady;
}

Camera2::~Camera2() {
    closeCamera();
}

bool Camera2::isSupportCamera2() {
    bool isSupport = false;
    auto fun = [&isSupport](const char *deviceId, const ACameraMetadata_const_entry& entry)->bool {
        if (entry.tag == ACAMERA_INFO_SUPPORTED_HARDWARE_LEVEL){
            if (ACAMERA_INFO_SUPPORTED_HARDWARE_LEVEL_LEGACY != entry.data.u8[0]){
                isSupport = true;
                return false;
            }
        }
        return true;
    };
    forEachMetaData(fun);
    return isSupport;
}

static void parseMetaData(const ACameraMetadata_const_entry &entry, CameraDeviceConfig &deviceConfig){
    switch (entry.tag){
        case ACAMERA_INFO_SUPPORTED_HARDWARE_LEVEL:
            break;
        case ACAMERA_LENS_FACING: {
            acamera_metadata_enum_android_lens_facing_t facing = static_cast<acamera_metadata_enum_android_lens_facing_t>(entry.data.u8[0]);
            deviceConfig.facing = convertFacing(facing);
        }break;
        case ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS:{
            const size_t STREAM_CONFIGURATION_SIZE = 4;
            const size_t STREAM_FORMAT_OFFSET = 0;
            const size_t STREAM_WIDTH_OFFSET = 1;
            const size_t STREAM_HEIGHT_OFFSET = 2;
            const size_t STREAM_IS_INPUT_OFFSET = 3;
            const int32_t *array = entry.data.i32;
            for (size_t i = 0; i < entry.count; i += STREAM_CONFIGURATION_SIZE){
                int32_t width = array[i + STREAM_WIDTH_OFFSET];
                int32_t height = array[i + STREAM_HEIGHT_OFFSET];
                int32_t format = array[i + STREAM_FORMAT_OFFSET];
                int32_t isInput = array[i + STREAM_IS_INPUT_OFFSET];
                if (isInput){
                    continue;
                }
                if (format != AIMAGE_FORMAT_YUV_420_888){
                    continue;
                }
                CameraSize cameraSize(width, height);
                deviceConfig.supportSizes.push_back(cameraSize);
            }
        }break;
        default:
            break;
    }
}

CameraConfig Camera2::getCameraConfig() {
    CameraConfig cameraConfig;
    CameraDeviceConfig cameraDeviceConfig;
    auto fun = [&cameraConfig, &cameraDeviceConfig](const char *deviceId, const ACameraMetadata_const_entry& entry)->bool {
        if (cameraDeviceConfig.cameraId != deviceId){
            if (!cameraDeviceConfig.cameraId.empty()){
                cameraConfig.deviceConfigs.push_back(cameraDeviceConfig);
                cameraDeviceConfig.clear();
            }
            cameraDeviceConfig.cameraId = deviceId;
        }
        parseMetaData(entry, cameraDeviceConfig);
        return true;
    };
    forEachMetaData(fun);
    if (!cameraDeviceConfig.cameraId.empty()){
        cameraConfig.deviceConfigs.push_back(cameraDeviceConfig);
    }
    return cameraConfig;
}

void Camera2::setCameraSize(int width, int height){
    mSize.width = width;
    mSize.height = height;
}

camera_status_t Camera2::openCamera(const char* cameraId) {
    camera_status_t cameraStatus = ACAMERA_ERROR_UNKNOWN;

    do {
        std::unique_ptr<ACameraManager, decltype(&ACameraManager_delete)> cameraManager(ACameraManager_create(), &ACameraManager_delete);
        if (!cameraManager){
            Log::e("Camera2::openCamera ACameraManager_create failed");
            assert(false);
            break;
        }
        if (ACAMERA_OK != (cameraStatus = ACameraManager_openCamera(cameraManager.get(), cameraId, &mDeviceStateCallbacks, &mACameraDevice))){
            Log::e("Camera2::openCamera ACameraManager_openCamera %d failed", cameraStatus);
            assert(false);
            break;
        }
        if (ACAMERA_OK != (cameraStatus = ACaptureSessionOutputContainer_create(&mACaptureSessionOutputContainer))){
            Log::e("Camera2::openCamera ACaptureSessionOutputContainer_create %d failed", cameraStatus);
            assert(false);
            break;
        }
        cameraStatus = ACAMERA_OK;
    }while (false);

    if (ACAMERA_OK != cameraStatus){
        closeCamera();
    }
    return cameraStatus;
}

camera_status_t Camera2::addSurface(ACameraDevice_request_template templateId, ANativeWindow *nativeWindow){
    camera_status_t cameraStatus = ACAMERA_ERROR_UNKNOWN;
    ACameraOutputTarget *target = nullptr;
    ACaptureSessionOutput *output = nullptr;
    do {
        ACaptureRequest *captureRequest = nullptr;
        auto iter = mACaptureRequests.find(templateId);
        if (iter == mACaptureRequests.end()){
            if (ACAMERA_OK != (cameraStatus = ACameraDevice_createCaptureRequest(mACameraDevice, templateId, &captureRequest))){
                Log::e("Camera2::createOutputTarget ACameraDevice_createCaptureRequest %d failed", cameraStatus);
                assert(false);
                break;
            }
            mACaptureRequests[templateId].captureRequest = captureRequest;
            iter = mACaptureRequests.find(templateId);
        }else{
            captureRequest = iter->second.captureRequest;
        }
        if (ACAMERA_OK != ACameraOutputTarget_create(nativeWindow, &target)){
            Log::e("Camera2::addSurface ACameraOutputTarget_create %d failed", cameraStatus);
            assert(false);
            break;
        }
        if (ACAMERA_OK != (cameraStatus = ACaptureRequest_addTarget(captureRequest, target))){
            Log::e("Camera2::addSurface ACaptureRequest_addTarget %d failed", cameraStatus);
            assert(false);
            break;
        }
        if (ACAMERA_OK != (cameraStatus = ACaptureSessionOutput_create(nativeWindow, &output))){
            Log::e("Camera2::addSurface ACaptureSessionOutput_create %d failed", cameraStatus);
            assert(false);
            break;
        }
        if (ACAMERA_OK != (cameraStatus = ACaptureSessionOutputContainer_add(mACaptureSessionOutputContainer, output))){
            Log::e("Camera2::addSurface ACaptureSessionOutputContainer_add %d failed", cameraStatus);
            assert(false);
            break;
        }
        iter->second.targets.push_back(target);
        mACaptureSessionOutputs.push_back(output);
        cameraStatus = ACAMERA_OK;
    }while (false);

    if (ACAMERA_OK != cameraStatus){
        if (nullptr != target){
            ACameraOutputTarget_free(target);
            target = nullptr;
        }
        if (nullptr != output){
            ACaptureSessionOutput_free(output);
            output = nullptr;
        }
    }
    return cameraStatus;
}

camera_status_t Camera2::start(){
    camera_status_t cameraStatus = ACAMERA_ERROR_UNKNOWN;

    do {
        if (nullptr != mACameraCaptureSession){
            ACameraCaptureSession_close(mACameraCaptureSession);
            mACameraCaptureSession = nullptr;
        }
        if (ACAMERA_OK != (cameraStatus = ACameraDevice_createCaptureSession(mACameraDevice, mACaptureSessionOutputContainer, &mSessionStateCallbacks, &mACameraCaptureSession))){
            Log::e("Camera2::start ACameraDevice_createCaptureSession %d failed", cameraStatus);
            assert(false);
            break;
        }
        std::vector<ACaptureRequest*> captureRequests;
        for (auto &pair : mACaptureRequests){
            captureRequests.push_back(pair.second.captureRequest);
        }
        if (ACAMERA_OK != (cameraStatus = ACameraCaptureSession_setRepeatingRequest(mACameraCaptureSession, nullptr, captureRequests.size(), captureRequests.data(), nullptr))){
            Log::e("Camera2::start ACameraCaptureSession_setRepeatingRequest %d failed", cameraStatus);
            assert(false);
            break;
        }
        cameraStatus = ACAMERA_OK;
    }while (false);
    return cameraStatus;
}

camera_status_t Camera2::stop(){
    camera_status_t cameraStatus = ACAMERA_ERROR_UNKNOWN;

    do {
        if (ACAMERA_OK != (cameraStatus = ACameraCaptureSession_stopRepeating(mACameraCaptureSession))){
            Log::e("Camera2::stop ACameraCaptureSession_stopRepeating %d failed", cameraStatus);
            assert(false);
            break;
        }
        cameraStatus = ACAMERA_OK;
    }while(false);
    if (nullptr != mACameraCaptureSession){
        ACameraCaptureSession_close(mACameraCaptureSession);
        mACameraCaptureSession = nullptr;
    }
    return cameraStatus;
}

void Camera2::removeAllSurface(){
    for (ACaptureSessionOutput *output : mACaptureSessionOutputs){
        ACaptureSessionOutputContainer_remove(mACaptureSessionOutputContainer, output);
        ACaptureSessionOutput_free(output);
    }
    mACaptureSessionOutputs.clear();

    for (auto &pair : mACaptureRequests){
        CaptureRequest &captureRequest = pair.second;
        for (ACameraOutputTarget *target : captureRequest.targets){
            ACaptureRequest_removeTarget(captureRequest.captureRequest, target);
            ACameraOutputTarget_free(target);
        }
        ACaptureRequest_free(captureRequest.captureRequest);
    }
    mACaptureRequests.clear();
    //ANativeWindow_release
}

void Camera2::closeCamera(){
    stop();
    removeAllSurface();
    if (nullptr != mACameraDevice){
        ACameraDevice_close(mACameraDevice);
        mACameraDevice = nullptr;
    }
    if (nullptr != mACaptureSessionOutputContainer){
        ACaptureSessionOutputContainer_free(mACaptureSessionOutputContainer);
        mACaptureSessionOutputContainer = nullptr;
    }
}

void Camera2::ACameraDevice_StateCallback(void *context, ACameraDevice *device) {
    Camera2 *pCamera2 = reinterpret_cast<Camera2*>(context);
    assert(nullptr != pCamera2);
    pCamera2->ACameraDevice_StateCallback(device);
}

void Camera2::ACameraDevice_ErrorStateCallback(void *context, ACameraDevice *device, int error) {
    Camera2 *pCamera2 = reinterpret_cast<Camera2*>(context);
    assert(nullptr != pCamera2);
    pCamera2->ACameraDevice_ErrorStateCallback(device, error);
}

void Camera2::ACameraDevice_StateCallback(ACameraDevice *device) {

}

void Camera2::ACameraDevice_ErrorStateCallback(ACameraDevice *device, int error) {

}

void Camera2::ACameraCaptureSession_stateCallback_onReady(void *context,
                                                          ACameraCaptureSession *session) {
    Camera2 *pCamera2 = reinterpret_cast<Camera2*>(context);
    assert(nullptr != pCamera2);
    pCamera2->ACameraCaptureSession_stateCallback_onReady(session);
}

void Camera2::ACameraCaptureSession_stateCallback_onActive(void *context,
                                                           ACameraCaptureSession *session) {
    Camera2 *pCamera2 = reinterpret_cast<Camera2*>(context);
    assert(nullptr != pCamera2);
    pCamera2->ACameraCaptureSession_stateCallback_onActive(session);
}

void Camera2::ACameraCaptureSession_stateCallback_onClosed(void *context,
                                                           ACameraCaptureSession *session) {
    Camera2 *pCamera2 = reinterpret_cast<Camera2*>(context);
    assert(nullptr != pCamera2);
    pCamera2->ACameraCaptureSession_stateCallback_onClosed(session);
}

void Camera2::ACameraCaptureSession_stateCallback_onReady(ACameraCaptureSession *session) {

}

void Camera2::ACameraCaptureSession_stateCallback_onActive(ACameraCaptureSession *session) {

}

void Camera2::ACameraCaptureSession_stateCallback_onClosed(ACameraCaptureSession *session) {

}

void Camera2::forEachMetaData(std::function<bool(const char *deviceId, const ACameraMetadata_const_entry &)> fun) {
    camera_status_t cameraStatus = ACAMERA_ERROR_UNKNOWN;
    do {
        assert(fun);
        std::unique_ptr<ACameraManager, decltype(&ACameraManager_delete)> cameraManager(ACameraManager_create(), &ACameraManager_delete);
        if (!cameraManager){
            Log::e("Camera2::isSupportCamera2 ACameraManager_create failed");
            assert(false);
            break;
        }
        ACameraIdList *tmpCameraIdList = nullptr;
        if (ACAMERA_OK != (cameraStatus = ACameraManager_getCameraIdList(cameraManager.get(), &tmpCameraIdList))){
            Log::e("Camera2::isSupportCamera2 ACameraManager_getCameraIdList %d failed", cameraStatus);
            assert(false);
            break;
        }
        std::unique_ptr<ACameraIdList, decltype(&ACameraManager_deleteCameraIdList)> cameraIdList(tmpCameraIdList, &ACameraManager_deleteCameraIdList);
        for (int i = 0; i < cameraIdList->numCameras; i++){
            const char* id = cameraIdList->cameraIds[i];
            ACameraMetadata *tmpMetaData = nullptr;
            if (ACAMERA_OK != (cameraStatus = ACameraManager_getCameraCharacteristics(cameraManager.get(), id, &tmpMetaData))){
                Log::e("Camera2::isSupportCamera2 ACameraManager_getCameraCharacteristics %d failed", cameraStatus);
                assert(false);
                continue;
            }
            std::unique_ptr<ACameraMetadata, decltype(&ACameraMetadata_free)> metadata(tmpMetaData, &ACameraMetadata_free);
            const uint32_t *tags = nullptr;
            int32_t count = 0;
            if (ACAMERA_OK != (cameraStatus = ACameraMetadata_getAllTags(metadata.get(), &count, &tags))){
                Log::e("Camera2::isSupportCamera2 ACameraMetadata_getAllTags %d failed", cameraStatus);
                assert(false);
                continue;
            }
            for (int tagIdx = 0; tagIdx < count; ++tagIdx){
                ACameraMetadata_const_entry lensInfo = {0};
                if (ACAMERA_OK != (cameraStatus = ACameraMetadata_getConstEntry(metadata.get(), tags[tagIdx], &lensInfo))){
                    Log::e("Camera2::isSupportCamera2 ACameraMetadata_getConstEntry %d failed", cameraStatus);
                    //assert(false);
                    continue;
                }
                if (!fun(id, lensInfo)){
                    break;
                }
            }
        }
    }while(false);
}
