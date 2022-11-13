cmake_minimum_required(VERSION 3.14)
project(EyeCandy3d)

# Project options
option(EYECANDY3D_BUILD_SAMPLES "Build all sample projects?" ON)
option(EYECANDY3D_BUILD_TESTS "Build unit tests?" ON)
option(EYECANDY3D_ALL_WARNINGS "Enable all compiler warnings?" OFF)

message("-------------------- OPTIONS --------------------")
message("Build samples: ${EYECANDY3D_BUILD_SAMPLES}")
message("Build tests: ${EYECANDY3D_BUILD_TESTS}")
message("Extra warnings: ${EYECANDY3D_ALL_WARNINGS}")
message("-------------------------------------------------")

# Setup cmake
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ec3_utils)

# Setup paths
set(EYECANDY3D_DEFAULT_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)

# Setup compiler options
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
set(CMAKE_CXX_STANDARD 20)

# Compiler configuration
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")

	set(warnings "")
	if(${EYECANDY3D_ALL_WARNINGS})
		set(warnings "-Wall -Wextra -Werror	\
			-Wno-error=unused-parameter \
			-Wno-error=unused-variable \
			-Wno-error=type-limits \
			-Wno-error=return-local-addr \
			-Wno-error=unused-function \
			-Wno-error=unused-but-set-variable \
			-Wno-error=implicit-fallthrough \
			-Wno-error=misleading-indentation")
	endif()
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# 	set(warnings "/W4 /WX /EHsc")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

# Setup dependencies
add_subdirectory(ThirdParty)

# Build library
add_subdirectory(lib)

# Build samples
if(EYECANDY3D_BUILD_SAMPLES)
	set(EYECANDY3D_SAMPLE_PREFIX "ec_sample_")
	add_subdirectory(samples)
endif()

# Test
if(EYECANDY3D_BUILD_TESTS)
	enable_testing()
	add_custom_target(CTest "-v")
	add_subdirectory(tests)
endif()

