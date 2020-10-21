cmake_minimum_required(VERSION 3.4.1)
set(targetName  "SDL2_image")

#add_definitions("-DLOAD_BMP -DLOAD_GIF -DLOAD_LBM -DLOAD_PCX -DLOAD_PNM -DLOAD_SVG -DLOAD_TGA -DLOAD_XCF -DLOAD_XPM -DLOAD_XV")
#add_definitions("-DLOAD_BMP -DLOAD_GIF -DLOAD_LBM -DLOAD_PCX -DLOAD_PNM -DLOAD_SVG -DLOAD_TGA -DLOAD_XCF -DLOAD_XPM -DLOAD_XV")

set(USE_PROJECT_CMAKE_MODULE_PATH "-DCMAKE_MODULE_PATH=${MAKE_MODULE_PATH}")
add_definitions("-DZ_SOLO")
set(zlibDir "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib-1.2.11")
add_subdirectory(${zlibDir})

set(ZLIB_INCLUDE_DIR "${zlibDir}")

#ExternalProject_Add(ZLIB
#        SOURCE_DIR ${zlibDir}
#        DOWNLOAD_COMMAND ""
#        UPDATE_COMMAND ""
#        CMAKE_ARGS
#        -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}
#        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
#        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
#        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        ${USE_PROJECT_CMAKE_MODULE_PATH}
#        INSTALL_COMMAND ""
#       )

set(jpgDir "${CMAKE_CURRENT_SOURCE_DIR}/external/jpeg-9b")
#add_subdirectory(${jpgDir} EXCLUDE_FROM_ALL)

set(PNG_SHARED OFF CACHE BOOL "stop build shared png")
set(PNG_STATIC ON CACHE BOOL "build static png")
set(PNG_TESTS OFF CACHE BOOL "stop build test")
set(PNG_BUILD_ZLIB ON CACHE BOOL "build zlib")
set(pngDir "${CMAKE_CURRENT_SOURCE_DIR}/external/libpng-1.6.32")
add_subdirectory(${pngDir} EXCLUDE_FROM_ALL)

set(webpDir "${CMAKE_CURRENT_SOURCE_DIR}/external/libwebp-0.6.0")
#add_subdirectory(${webpDir} EXCLUDE_FROM_ALL)

set(sdl2ImageDir "${CMAKE_CURRENT_SOURCE_DIR}")
set(sdlDir "${CMAKE_CURRENT_SOURCE_DIR}/../SDL")

include_directories(
        ${sdlDir}/include
)

add_library(
        SDL2_image

        SHARED

        IMG.c
        IMG_bmp.c
        IMG_gif.c
        IMG_jpg.c
        IMG_lbm.c
        IMG_pcx.c
        IMG_png.c
        IMG_pnm.c
        IMG_svg.c
        IMG_tga.c
        IMG_tif.c
        IMG_webp.c
        IMG_WIC.c
        IMG_xcf.c
        IMG_xpm.c
        IMG_xv.c
        IMG_xxx.c
)

target_link_libraries(
        SDL2_image

        png
)