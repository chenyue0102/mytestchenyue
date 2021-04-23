# CMakeList.txt: webrtc 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
project(webrtcagc)

set(webrtcDir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

if (ANDROID)
	add_definitions(-DWEBRTC_POSIX -DWEBRTC_ANDROID -DWEBRTC_LINUX -DWEBRTC_ARCH_ARM -DWEBRTC_APM_DEBUG_DUMP=0 -DABSL_USES_STD_STRING_VIEW)
elseif (APPLE)
	add_definitions(-DWEBRTC_POSIX -DWEBRTC_IOS -DWEBRTC_ARCH_ARM -DWEBRTC_APM_DEBUG_DUMP=0 -DABSL_USES_STD_STRING_VIEW)
elseif (WIN32)
	add_definitions(-DWEBRTC_WIN -DWIN32_LEAN_AND_MEAN -DWEBRTC_APM_DEBUG_DUMP=0 -DNOMINMAX -DABSL_USES_STD_STRING_VIEW)
else()
    message(FATAL_ERROR "platform not support")
endif()

include_directories(
	${webrtcDir}
)

#webrtc混音模块共用
set(webrtcMux 
	${webrtcDir}/rtc_base/checks.cc
	${webrtcDir}/common_audio/audio_util.cc
	${webrtcDir}/modules/audio_processing/logging/apm_data_dumper.cc
	${webrtcDir}/rtc_base/logging.cc
	${webrtcDir}/system_wrappers/source/field_trial.cc    
	${webrtcDir}/rtc_base/string_encode.cc
	${webrtcDir}/rtc_base/strings/string_builder.cc
	${webrtcDir}/rtc_base/platform_thread_types.cc
	${webrtcDir}/rtc_base/string_utils.cc
	${webrtcDir}/rtc_base/time_utils.cc
	${webrtcDir}/rtc_base/system_time.cc
)
add_library(absl_base STATIC IMPORTED)
set_property(TARGET absl_base PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../absl_base.lib")

add_library(absl_throw_delegate STATIC IMPORTED)
set_property(TARGET absl_throw_delegate PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../absl_throw_delegate.lib")

add_library(absl_strings STATIC IMPORTED)
set_property(TARGET absl_strings PROPERTY IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/../absl_strings.lib")
#copy_set_operations.c division_operations.c resample_by_2.c spl_inl.c spl_sqrt.c是c文件
add_library(
	webrtcagc

	STATIC

	 ${webrtcDir}/modules/audio_processing/gain_control_impl.cc
        ${webrtcDir}/modules/audio_processing/audio_buffer.cc
        ${webrtcDir}/modules/audio_processing/splitting_filter.cc
        ${webrtcDir}/modules/audio_processing/three_band_filter_bank.cc
        ${webrtcDir}/modules/audio_processing/agc/legacy/digital_agc.cc
        ${webrtcDir}/modules/audio_processing/agc/legacy/analog_agc.cc

        ${webrtcDir}/common_audio/resampler/push_sinc_resampler.cc
        ${webrtcDir}/common_audio/resampler/sinc_resampler.cc
        ${webrtcDir}/common_audio/resampler/sinc_resampler_avx2.cc
        ${webrtcDir}/common_audio/resampler/sinc_resampler_sse.cc
        ${webrtcDir}/common_audio/signal_processing/dot_product_with_scale.cc

        ${webrtcDir}/common_audio/signal_processing/copy_set_operations.c
        ${webrtcDir}/common_audio/signal_processing/division_operations.c
        ${webrtcDir}/common_audio/signal_processing/resample_by_2.c
        ${webrtcDir}/common_audio/signal_processing/spl_inl.c
        ${webrtcDir}/common_audio/signal_processing/spl_sqrt.c
        ${webrtcDir}/common_audio/signal_processing/splitting_filter.c

        ${webrtcDir}/rtc_base/memory/aligned_malloc.cc
        ${webrtcDir}/modules/audio_processing/gain_control_impl.cc
        ${webrtcDir}/modules/audio_processing/audio_buffer.cc
        ${webrtcDir}/modules/audio_processing/splitting_filter.cc
        ${webrtcDir}/modules/audio_processing/three_band_filter_bank.cc
        ${webrtcDir}/modules/audio_processing/agc/legacy/digital_agc.cc
        ${webrtcDir}/modules/audio_processing/agc/legacy/analog_agc.cc

        ${webrtcDir}/common_audio/resampler/push_sinc_resampler.cc
        ${webrtcDir}/common_audio/resampler/sinc_resampler.cc
        ${webrtcDir}/common_audio/signal_processing/dot_product_with_scale.cc

        ${webrtcDir}/common_audio/signal_processing/copy_set_operations.c
        ${webrtcDir}/common_audio/signal_processing/division_operations.c
        ${webrtcDir}/common_audio/signal_processing/resample_by_2.c
        ${webrtcDir}/common_audio/signal_processing/spl_inl.c
        ${webrtcDir}/common_audio/signal_processing/spl_sqrt.c
        ${webrtcDir}/common_audio/signal_processing/splitting_filter.c

        ${webrtcDir}/rtc_base/memory/aligned_malloc.cc

        ${webrtcDir}/system_wrappers/source/cpu_features.cc

	${webrtcMux}
)

target_link_libraries(
	webrtcagc
	absl_base
	absl_throw_delegate
	absl_strings
    winmm.lib
)