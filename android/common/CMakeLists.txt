cmake_minimum_required(VERSION 3.4.1)
project(CommonLib)
set(CommonLib_VERSION_MAJOR 1)
set(CommonLib_VERSION_MINOR 0)
SET(CMAKE_CXX_FLAGS "-lpthread")

add_library(CommonLib
        STATIC
        Log.cpp
        MyLock.cpp
        OpenSLESHelper.cpp
        RingQueue.cpp
        SystemTime.cpp
        TaskPool.cpp
        )

target_link_libraries(
        CommonLib
)