# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(JNILIBS ${CMAKE_CURRENT_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})
set(LAME ${CMAKE_CURRENT_SOURCE_DIR}/include/lame)

include_directories(
        ${LAME}
)
# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             TestMedia.cpp
            OpenSLESHelper.cpp
            LameHelper.cpp
            Mp3Player.cpp
            TaskPool.cpp
            RingQueue.cpp
            JniHelper.cpp
            SystemTime.cpp
            Log.cpp
        )

add_library(libmp3lame STATIC IMPORTED)
set_target_properties(libmp3lame PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libmp3lame.a)

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

#基础库放到最后,否则会提示库无法找到
target_link_libraries( # Specifies the target library.
                       native-lib
                        libmp3lame
                       # Links the target library to the log library
                       # included in the NDK.
        OpenSLES
        android
                       ${log-lib} )