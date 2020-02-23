cmake_minimum_required(VERSION 3.4.1)
project(TCPServer)
set(TCPServer_VERSION_MAJOR 1)
set(TCPServer_VERSION_MINOR 0)
SET(CMAKE_CXX_FLAGS "-lpthread")

add_library(TCPServer
        STATIC
        TCPServer.cpp
        EPollObject.cpp
        Log.cpp
        )

target_link_libraries(
        TCPServer
)