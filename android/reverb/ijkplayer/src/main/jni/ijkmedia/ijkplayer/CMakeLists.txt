# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)
project(ijkplayer)
set(ijkplayerDir ${CMAKE_CURRENT_SOURCE_DIR})
set(ffmpegincludeDir ${CMAKE_CURRENT_SOURCE_DIR}/../../ffmpeg-armv7a/output/include)
set(ffmpeglibDir ${CMAKE_CURRENT_SOURCE_DIR}/../../../jniLibs/armeabi-v7a)
set(ijkj4aDir ${CMAKE_CURRENT_SOURCE_DIR}/../ijkj4a)
set(profDir ${CMAKE_CURRENT_SOURCE_DIR}/../../android-ndk-prof)

include_directories(
        ${ijkplayerDir}
        ${ijkplayerDir}/../
        ${ffmpegincludeDir}
        ${ijkj4aDir}
)

link_directories(
        ${ffmpeglibDir}
)


add_library(
        ijkplayer

        SHARED

        ff_cmdutils.c
        ff_ffplay.c
        ff_ffpipeline.c
        ff_ffpipenode.c
        ijkmeta.c
        ijkplayer.c

        pipeline/ffpipeline_ffplay.c
        pipeline/ffpipenode_ffplay_vdec.c

        android/ffmpeg_api_jni.c
        android/ijkplayer_android.c
        android/ijkplayer_jni.c

        android/pipeline/ffpipeline_android.c
        android/pipeline/ffpipenode_android_mediacodec_vdec.c

        ijkavformat/allformats.c
        ijkavformat/cJSON.c
        ijkavformat/ijklas.c
        ijkavformat/ijklivehook.c
        ijkavformat/ijkmediadatasource.c
        ijkavformat/ijkio.c
        ijkavformat/ijkiomanager.c
        ijkavformat/ijkiocache.c
        ijkavformat/ijkioffio.c
        ijkavformat/ijkioandroidio.c
        ijkavformat/ijkioprotocol.c
        ijkavformat/ijkioapplication.c
        ijkavformat/ijkiourlhook.c

        ijkavformat/ijkasync.c
        ijkavformat/ijkurlhook.c
        ijkavformat/ijklongurl.c
        ijkavformat/ijksegment.c

        ijkavutil/ijkdict.c
        ijkavutil/ijkutils.c
        ijkavutil/ijkthreadpool.c
        ijkavutil/ijktree.c
        ijkavutil/ijkfifo.c
        ijkavutil/ijkstl.cpp

        ${profDir}/prof.c
)

target_link_libraries(
        ijkplayer

        ijksdl
        ijkffmpeg
        ijksoundtouch

        log
        android
)