# CMakeList.txt: webrtc 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(webrtcagcDir ${CMAKE_CURRENT_SOURCE_DIR}/agc)
set(webrtcDir ${CMAKE_CURRENT_SOURCE_DIR}/../)

include_directories(
	${webrtcDir}
)

add_subdirectory(${webrtcagcDir} webrtcagc)

# 将源代码添加到此项目的可执行文件。
add_executable (webrtcexe "webrtcdemo.cpp" "webrtcdemo.h")

target_link_libraries(
	webrtcexe
	
	webrtcagc
)
