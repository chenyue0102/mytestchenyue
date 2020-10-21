# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(targetName  "native-lib")

#add_definitions("-DSPINE_SHORT_NAMES")

set(sdlDir "${CMAKE_CURRENT_SOURCE_DIR}/SDL")
add_subdirectory(${sdlDir})
set(SDL2MAIN_LIBRARY SDL2main)
set(SDL2_LIBRARY SDL2)

#set(sdl2ImageDir "${CMAKE_CURRENT_SOURCE_DIR}/SDL2_image")
#add_subdirectory(${sdl2ImageDir})

set(spineDir "${CMAKE_CURRENT_SOURCE_DIR}/spine-c")
add_subdirectory(${spineDir})


set(spinesdlDir "${CMAKE_CURRENT_SOURCE_DIR}/spine-sdl")
add_subdirectory(${spinesdlDir})


# Joysticks were causing trouble on android.
add_definitions(-DSDL_JOYSTICK=0)

# Include dirs.
include_directories(
        "${sdlDir}/include"
        ${spineDir}/spine-c/include/spine
        ${spineDir}/spine-c/include
        )


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

if(WIN32)
add_executable(SDLMain SDLMain.cpp)
else()
add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             native-lib.cpp
            SDLMain.cpp)
endif()			

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.
if(ANDROID)
find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )
endif()

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
if(WIN32)
target_link_libraries( # Specifies the target library.
SDLMain
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        spine-c
        spine-sdl)
else()
target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
        ${SDL2MAIN_LIBRARY}
        ${SDL2_LIBRARY}
        spine-c
        spine-sdl
        GLESv2)
endif()