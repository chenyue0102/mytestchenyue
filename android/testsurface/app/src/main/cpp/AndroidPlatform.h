//
// Created by EDZ on 2020/12/11.
//

#ifndef TESTSURFACE_ANDROIDPLATFORM_H
#define TESTSURFACE_ANDROIDPLATFORM_H

#include <assert.h>
#include <camera/NdkCameraMetadataTags.h>
#include "StructDefine.h"


inline CameraFacing convertFacing(acamera_metadata_enum_android_lens_facing_t facing){
    CameraFacing ret = CameraFacingFront;
    switch (facing){
        case ACAMERA_LENS_FACING_FRONT:
            ret = CameraFacingFront;
            break;
        case ACAMERA_LENS_FACING_BACK:
            ret = CameraFacingBack;
            break;
        default:
            assert(false);
            break;
    }
    return ret;
}


#endif //TESTSURFACE_ANDROIDPLATFORM_H
