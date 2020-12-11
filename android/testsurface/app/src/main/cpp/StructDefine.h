//
// Created by EDZ on 2020/12/11.
//

#ifndef TESTSURFACE_STRUCTDEFINE_H
#define TESTSURFACE_STRUCTDEFINE_H
#include <vector>
#include <string>

enum CameraFacing{
    CameraFacingFront = 0,          //0
    CameraFacingBack = 1,           //1
};

struct CameraSize{
    int width;
    int height;

    CameraSize():width(0), height(0){}
    CameraSize(int _width, int _height):width(_width), height(_height){}
};

struct CameraDeviceConfig{
    std::string cameraId;
    CameraFacing facing;
    std::vector<CameraSize> supportSizes;

    CameraDeviceConfig(){
        clear();
    }
    void clear(){
        cameraId.clear();
        facing = CameraFacingFront;
        supportSizes.clear();
    }
};

struct CameraConfig{
    std::vector<CameraDeviceConfig> deviceConfigs;
};

#endif //TESTSURFACE_STRUCTDEFINE_H
