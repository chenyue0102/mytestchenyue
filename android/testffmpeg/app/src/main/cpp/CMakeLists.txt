# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(JNILIBS ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
set(COMMON ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../common)
set(MYINCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../../../../../include)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/lame
        ${CMAKE_CURRENT_SOURCE_DIR}/include/fdk-aac
        ${COMMON}
        ${MYINCLUDE}
)

#add_subdirectory(${COMMON} common_binary_dir)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
        native-lib.cpp
        EncodeHelper.cpp
        FFMPEGTest.cpp
        PlayManager.cpp
        FrameReceive.cpp
        Demuxer.cpp

        ${COMMON}/BitBuffer.cpp
        ${COMMON}/OpenGLHelper.cpp
        ${COMMON}/RenderYUV420P.cpp
        ${COMMON}/OpenGLPlay.cpp
        ${COMMON}/OpenSLPlay.cpp
        ${COMMON}/ClockTime.cpp
        ${COMMON}/Log.cpp
        ${COMMON}/OpenSLESHelper.cpp
        ${COMMON}/RingQueue.cpp
        ${COMMON}/BaseTime.cpp
        ${COMMON}/TaskPool.cpp
        )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

find_library(libz-lib libz.so)

add_library(libavcodec STATIC IMPORTED)
set_target_properties(libavcodec PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libavcodec.a)

add_library(libavfilter STATIC IMPORTED)
set_target_properties(libavfilter PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libavfilter.a)

add_library(libavformat STATIC IMPORTED)
set_target_properties(libavformat PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libavformat.a)

add_library(libswresample STATIC IMPORTED)
set_target_properties(libswresample PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libswresample.a)

add_library(libswscale STATIC IMPORTED)
set_target_properties(libswscale PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libswscale.a)

add_library(libavutil STATIC IMPORTED)
set_target_properties(libavutil PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libavutil.a)

add_library(libfdk-aac STATIC IMPORTED)
set_target_properties(libfdk-aac PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libfdk-aac.a)

add_library(libmp3lame STATIC IMPORTED)
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libmp3lame.a)

add_library(libx264 STATIC IMPORTED)
set_target_properties(libx264 PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libx264.a)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

        libavformat
        libavfilter
        libswscale
        libswresample
        libavcodec
        libavutil
        libfdk-aac
        libmp3lame
        libx264
                       # Links the target library to the log library
                       # included in the NDK.
        #CommonLib

        OpenSLES
        GLESv3
        android

                       ${log-lib}
        ${libz-lib})