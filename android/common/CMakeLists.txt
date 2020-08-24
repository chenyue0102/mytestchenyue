cmake_minimum_required(VERSION 3.4.1)
project(CommonLib)
set(CommonLib_VERSION_MAJOR 1)
set(CommonLib_VERSION_MINOR 0)
SET(CMAKE_CXX_FLAGS "-lpthread")

add_library(CommonLib
        STATIC
        OpenGLHelper.cpp
        RenderYUV420P.cpp
        OpenGLPlay.cpp
        OpenSLPlay.cpp
        ClockTime.cpp
        Log.cpp
        OpenSLESHelper.cpp
        RingQueue.cpp
        BaseTime.cpp
        TaskPool.cpp
        )

target_link_libraries(
        CommonLib
        GLESv3
)