cmake_minimum_required(VERSION 3.4.1)
project(spine-sdl)
set(SDL_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../SDL/include)
set(SPINE_C_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/../spine-c/spine-c/include)

include_directories(
        ${SDL_INCLUDE}
        ${SPINE_C_INCLUDE}
)

add_library(
        spine-sdl
        STATIC
        #SHARED

        spine-sdl.cpp
)