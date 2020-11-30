cmake_minimum_required(VERSION 3.8.1)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project("EyeCandy3D")
set(PROJECT_SHORT_NAME "EC3D")

set(CMAKE_CXX_STANDARD 20)

#################################################
# OPTIONS
#################################################

option(EYECANDY3D_BUILD_SAMPLES "Build all sample projects?" ON)
option(EYECANDY3D_BUILD_TESTS "Build unit tests?" ON)

option(EYECANDY3D_ALL_WARNINGS "Enable all compiler warnings?" OFF)

#################################################
# GENERAL
#################################################

# Configure install paths
set(EYECANDY3D_INCLUDE_DIRECTORY EyeCandy3D/include/)
set(EYECANDY3D_LIBRARY_INSTALL_PATH lib)
set(EYECANDY3D_INCLUDE_INSTALL_PATH include/)

# Configure output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(EYECANDY3D_TEST_NAME "Test")
set(EYECANDY3D_SAMPLE_PREFIX "ec_sample_")

#################################################
# COMPILER OPTIONS
#################################################

# Build configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
	SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()
SET(CMAKE_DEBUG_POSTFIX "d")

# Compiler options
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

set(CMAKE_C_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
set(CMAKE_CXX_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)

#################################################
# DEPENDENCIES
#################################################

# Find packages
find_package(Freetype REQUIRED)

# Dependency variables
set(EYECANDY3D_DEPENDENCIES
		agui
		glfw
		GLEW
		GLU
		GL
		X11
		Xrandr
		Xinerama
		Xi
		Xxf86vm
		Xcursor
		pthread
		dl
		freetype)

set(EYECANDY3D_ALL_DEPENDENCIES ${EYECANDY3D_DEPENDENCIES})


include_directories(${FREETYPE_INCLUDE_DIRS}
		EyeCandy3D/include)

#################################################
# BUILD
#################################################

# Build library
add_subdirectory(EyeCandy3D)

# Build samples
if(${EYECANDY3D_BUILD_SAMPLES})
add_subdirectory(Samples)
endif()

# Test
if(${EYECANDY3D_BUILD_TESTS})
enable_testing()
add_subdirectory(Test)
add_test(NAME ${EYECANDY3D_TEST_NAME}
		COMMAND ${EYECANDY3D_TEST_NAME} --config $<CONFIGURATION>
		--exe $<TARGET_FILE:${EYECANDY3D_TEST_NAME}>)
endif()

#################################################
# INSTALLATION
#################################################

# Install library and header files
install(TARGETS ${PROJECT_NAME}
		LIBRARY	DESTINATION ${EYECANDY3D_LIBRARY_INSTALL_PATH})

install(DIRECTORY include/EC3D
		DESTINATION include)

