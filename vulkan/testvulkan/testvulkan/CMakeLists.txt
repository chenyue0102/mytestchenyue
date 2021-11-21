# CMakeList.txt: testvulkan 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

option(AUTO_LOCATE_VULKAN "AUTO_LOCATE_VULKAN" ON)

if (AUTO_LOCATE_VULKAN)
	message(STATUS "finding vulkan using cmake")
endif()

find_package(Vulkan)

if(NOT ${Vulkan_INCLUDE_DIRS} STREQUAL "")
	set(VULKAN_PATH ${Vulkan_INCLUDE_DIRS})
	#Vulkan_INCLUDE_DIRS为include文件夹地址，替换为上一次地址
	STRING(REGEX REPLACE "/Include" "" VULKAN_PATH ${VULKAN_PATH})
	message(STATUS ${VULKAN_PATH})
else()
	message(STATUS "vulkan not found")
endif()

if (WIN32)
	message(STATUS "win32 define")
	add_definitions(-DVK_USE_PLAFORM_WIN32_KHR)
	include_directories(${VULKAN_PATH}/Include)
	link_directories(${VULKAN_PATH}/Lib)
endif()

# 将源代码添加到此项目的可执行文件。
add_executable (testvulkan "testvulkan.cpp" "testvulkan.h")

# TODO: 如有需要，请添加测试并安装目标。
target_link_libraries(
	testvulkan
	vulkan-1
)