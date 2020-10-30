cmake_minimum_required(VERSION 3.4.1)
project(Spine)
set(Spine_VERSION_MAJOR 1)
set(Spine_VERSION_MINOR 0)

if(MSVC)
    message("MSCV detected")
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
    set (CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c89")
    #set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -pedantic -std=c++03 -fno-exceptions -fno-rtti")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -pedantic -std=c++11 -fno-exceptions -fno-rtti")
endif()


set(spinecppDir ${CMAKE_CURRENT_SOURCE_DIR}/../spine-cpp)
set(spineDir ${CMAKE_CURRENT_SOURCE_DIR})

#add_subdirectory(${spinecppDir} common_binary_dir)

file(GLOB INCLUDES "${spinecppDir}/spine-cpp/include/**/*.h")
file(GLOB SOURCES "${spinecppDir}/spine-cpp/src/**/*.cpp")

include_directories(
        ${spinecppDir}/spine-cpp/include
        ${spineDir}/include
)

#add_library(
#        spine-cpp
#        STATIC
#        ${SOURCES}
#        ${INCLUDES}
#)

add_library(
        Spine

        STATIC

        ${SOURCES}
        source/SpineItem.cpp
        source/RenderCmdsCache.cpp
        source/MyTexture.cpp
        source/texture.cpp
        source/OpenGLESHelper.cpp
        source/StructDefine.cpp
        source/BaseTime.cpp
        source/Log.cpp
)

target_link_libraries(
        Spine
        GLESv3
)