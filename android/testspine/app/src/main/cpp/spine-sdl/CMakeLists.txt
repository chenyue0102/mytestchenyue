cmake_minimum_required(VERSION 3.4.1)
project(spine-sdl)

#add_definitions("-DSPINE_SHORT_NAMES")

set(SDL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../SDL/include)
set(SDL_IMAGE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../SDL2_image)
set(SPINE_C_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../spine-c/spine-c/include)

include_directories(
        ${SDL_INCLUDE}
        ${SDL_IMAGE_INCLUDE}
        ${SPINE_C_INCLUDE}
        ${SPINE_C_INCLUDE}/spine
)


#set(spineDir "${CMAKE_CURRENT_SOURCE_DIR}/../spine-c")
#add_subdirectory(${spineDir} common_binary_dir)

add_library(
        spine-sdl
        STATIC
        #SHARED

        spine-sdl.cpp
)

target_link_libraries(
        spine-sdl
        spine-c
)