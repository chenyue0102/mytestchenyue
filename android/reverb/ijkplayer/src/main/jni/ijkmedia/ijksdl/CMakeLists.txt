# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
project(ijksdl)
cmake_minimum_required(VERSION 3.4.1)

set(ijksdlDir ${CMAKE_CURRENT_SOURCE_DIR})
set(ijkyuvDir ${CMAKE_CURRENT_SOURCE_DIR}/../ijkyuv)
set(ijkj4aDir ${CMAKE_CURRENT_SOURCE_DIR}/../ijkj4a)
set(ffmpegincludeDir ${CMAKE_CURRENT_SOURCE_DIR}/../../ffmpeg-armv7a/output/include)
set(ffmpeglibDir ${CMAKE_CURRENT_SOURCE_DIR}/../../../jniLibs/armeabi-v7a)

include_directories(
        ${ijksdlDir}
        ${ijksdlDir}/../
        ${ffmpegincludeDir}
        ${ijkyuvDir}/include
        ${ijkj4aDir}
)

link_directories(
        ${ffmpeglibDir}
)

add_library(
        ijksdl

        SHARED

        ijksdl_aout.c
        ijksdl_audio.c
        ijksdl_egl.c
        ijksdl_error.c
        ijksdl_mutex.c
        ijksdl_stdinc.c
        ijksdl_thread.c
        ijksdl_timer.c
        ijksdl_vout.c
        ijksdl_extra_log.c
        gles2/color.c
        gles2/common.c
        gles2/renderer.c
        gles2/renderer_rgb.c
        gles2/renderer_yuv420p.c
        gles2/renderer_yuv444p10le.c
        gles2/shader.c
        gles2/fsh/rgb.fsh.c
        gles2/fsh/yuv420p.fsh.c
        gles2/fsh/yuv444p10le.fsh.c
        gles2/vsh/mvp.vsh.c

        dummy/ijksdl_vout_dummy.c

        ffmpeg/ijksdl_vout_overlay_ffmpeg.c
        ffmpeg/abi_all/image_convert.c

        android/android_audiotrack.c
        android/android_nativewindow.c
        android/ijksdl_android_jni.c
        android/ijksdl_aout_android_audiotrack.c
        android/ijksdl_aout_android_opensles.c
        android/ijksdl_codec_android_mediacodec_dummy.c
        android/ijksdl_codec_android_mediacodec_internal.c
        android/ijksdl_codec_android_mediacodec_java.c
        android/ijksdl_codec_android_mediacodec.c
        android/ijksdl_codec_android_mediadef.c
        android/ijksdl_codec_android_mediaformat_java.c
        android/ijksdl_codec_android_mediaformat.c
        android/ijksdl_vout_android_nativewindow.c
        android/ijksdl_vout_android_surface.c
        android/ijksdl_vout_overlay_android_mediacodec.c
)

target_link_libraries(
        ijksdl

        ijkj4a
        #ijkyuv
        ijkffmpeg
        yuv

        log
        android
        OpenSLES
        EGL
        GLESv2
        #cpufeatures
)