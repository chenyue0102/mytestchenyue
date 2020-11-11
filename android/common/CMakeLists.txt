cmake_minimum_required(VERSION 3.4.1)
project(CommonLib)
set(CommonLib_VERSION_MAJOR 1)
set(CommonLib_VERSION_MINOR 0)
SET(CMAKE_CXX_FLAGS "-lpthread")
set(MYINCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

#set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

include_directories(
        ${MYINCLUDE}
)

add_library(CommonLib
        STATIC
        #SHARED

        BitBuffer.cpp
        OpenGLHelper.cpp
        RenderYUV420P.cpp
        OpenGLPlay.cpp
        OpenSLPlay.cpp
        ClockTime.cpp
        Log.c
        OpenSLESHelper.cpp
        RingQueue.cpp
        BaseTime.cpp
        TaskPool.cpp
        )

target_link_libraries(
        CommonLib
        GLESv3
)