# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
project(spinewrap)
cmake_minimum_required(VERSION 3.4.1)

set(spinecppDir ${CMAKE_CURRENT_SOURCE_DIR}/spine-cpp)
set(spineDir ${CMAKE_CURRENT_SOURCE_DIR}/Spine)

include_directories(
        ${spinecppDir}/spine-cpp/include
        ${spineDir}/include
)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#add_subdirectory(${spinecppDir})
add_subdirectory(${spineDir})

add_library( # Sets the name of the library.
            spinewrap

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
            jni/JNI.cpp
            jni/JniHelper.cpp
            jni/ShareData.cpp
            jni/SpineItemJNI.cpp
            jni/SkeletonJNI.cpp
            jni/RenderCmdsCacheJNI.cpp
            jni/TextureLoaderJNI.cpp
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

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        spinewrap

                       # Links the target library to the log library
                       # included in the NDK.
        Spine

        GLESv3
                       ${log-lib} )