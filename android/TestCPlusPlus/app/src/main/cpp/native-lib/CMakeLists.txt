# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
set(JNILIBS ${CMAKE_CURRENT_SOURCE_DIR}/../../jniLibs/${ANDROID_ABI})
set(NEPTUNE ${CMAKE_CURRENT_SOURCE_DIR}/../Neptune)
set(PLATINUM ${CMAKE_CURRENT_SOURCE_DIR}/../Platinum)
set(TCPSERVER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../TCPServer)

#add_subdirectory(${TCPSERVER_PATH} TCPServer)

include_directories(
        ${NEPTUNE}/Core
        ${PLATINUM}/Core
        ${PLATINUM}/Devices
        ${PLATINUM}/Devices/MediaConnect
        ${PLATINUM}/Devices/MediaRenderer
        ${PLATINUM}/Devices/MediaServer
        ${PLATINUM}/Extras
        ${PLATINUM}/Platinum
        ${TCPSERVER_PATH}
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
             native-lib.cpp
        ${TCPSERVER_PATH}/TCPServer.cpp
        ${TCPSERVER_PATH}/ServerObject.cpp
        ${TCPSERVER_PATH}/EPollObject.cpp
        ${TCPSERVER_PATH}/TaskPool.cpp
        ${TCPSERVER_PATH}/Log.cpp
        )

add_library(libaxTLS STATIC IMPORTED)
set_target_properties(libaxTLS PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libaxTLS.a)

add_library(libNeptune STATIC IMPORTED)
set_target_properties(libNeptune PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libNeptune.a)

add_library(libPlatinum STATIC IMPORTED)
set_target_properties(libPlatinum PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libPlatinum.a)

add_library(libPltMediaConnect STATIC IMPORTED)
set_target_properties(libPltMediaConnect PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libPltMediaConnect.a)

add_library(libPltMediaRenderer STATIC IMPORTED)
set_target_properties(libPltMediaRenderer PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libPltMediaRenderer.a)

add_library(libPltMediaServer STATIC IMPORTED)
set_target_properties(libPltMediaServer PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libPltMediaServer.a)

add_library(libZlib STATIC IMPORTED)
set_target_properties(libZlib PROPERTIES IMPORTED_LOCATION ${JNILIBS}/libZlib.a)

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
        libPlatinum
        libPltMediaConnect
        libPltMediaRenderer
        libPltMediaServer
        libNeptune
        libaxTLS
        libZlib
        #TcpServer
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )