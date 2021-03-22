cmake_minimum_required(VERSION 3.16)

include("cmake/HunterGate.cmake")
HunterGate(
		URL "https://github.com/cpp-pm/hunter/archive/v0.23.296.tar.gz"
		SHA1 "232f5022ee1d45955a7e8d3e1720f31bac1bb534"
)

project("EyeCandy3d")
set(PROJECT_SHORT_NAME "EC3D")

#################################################
# USER CONFIGURATION
#################################################

option(EYECANDY3D_BUILD_SAMPLES "Build all sample projects?" ON)
option(EYECANDY3D_BUILD_TESTS "Build unit tests?" ON)

set(EC_DEV_ALL_WARNINGS 1)
set(EC_DEV_WARNINGS_AS_ERRORS 0)
set(EC_DEV_ANNOYING_WARNINGS 0)
set(EC_DEV_USELESS_WARNINGS 0)

#################################################
# DEVELOPER CONFIGURATION
#################################################
set(EC_VERSION_MAJOR   "1")
set(EC_VERSION_MINOR   "0")
set(EC_VERSION_PATCH   "0")
set(EC_VERSION         "1.0.0")

set(EC_OPENGL_VERSION_MAJOR "3")
set(EC_OPENGL_VERSION_MINOR "3")
set(EC_OPENGL_VERSION_PATCH "0")
set(EC_OPENGL_VERSION       "3.3.0")

#################################################
# CONFIGURATION FILE
#################################################

# Configuration file setup
set(EC_CONFIGURATION_PATH "${CMAKE_SOURCE_DIR}/EyeCandy3D/include/EC3D/Common/Config.h")
configure_file("${EC_CONFIGURATION_PATH}.in"
		"${EC_CONFIGURATION_PATH}"
		@ONLY)

#################################################
# GENERAL CONFIGURATION
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

# Build configuration types: TODO
#SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
#IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
#	SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
#ENDIF()
#SET(CMAKE_DEBUG_POSTFIX "d")

# Warnings
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	if(${EC_DEV_ALL_WARNINGS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
		if(${EC_DEV_ANNOYING_WARNINGS})
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
		endif()
		if(${EC_DEV_USELESS_WARNINGS})
			# NOTHING TO DO
		else()
			# Maybe add this:
			#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") '
		endif()
	endif()
	if(${EC_DEV_WARNINGS_AS_ERRORS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
	endif()
else()
	if(${EC_DEV_ALL_WARNINGS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wpedantic")
		if(${EC_DEV_ANNOYING_WARNINGS})
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
		endif()
		if(${EC_DEV_USELESS_WARNINGS})
			# NOTHING TO DO
		else()
			set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-reorder -Wno-unused-variable")
		endif()
	endif()
	if(${EC_DEV_WARNINGS_AS_ERRORS})
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
	endif()
endif()

# C++ Version
set(CMAKE_CXX_STANDARD 17)

#################################################
# DEPENDENCIES
#################################################

hunter_add_package(glm)
find_package(glm REQUIRED)

#hunter_add_package(glfw)
#find_package(glfw3 REQUIRED)

hunter_add_package(freetype)
find_package(freetype CONFIG REQUIRED)

# Dependency variables

if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	hunter_add_package(glfw)
	find_package(glfw3 REQUIRED)

	hunter_add_package(glew)
	find_package(glew3 CONFIG REQUIRED)

	set(EYECANDY3D_DEPENDENCIES
			agui
			glm
			glfw3
			glew
			opengl32
			freetype)
else()
	find_package(X11)

	set(EYECANDY3D_DEPENDENCIES
			agui
			glm
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
endif()


set(EYECANDY3D_ALL_DEPENDENCIES ${EYECANDY3D_DEPENDENCIES} ${PROJECT_NAME})


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
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	# TODO
else()
	install(TARGETS ${PROJECT_NAME}
			LIBRARY	DESTINATION ${EYECANDY3D_LIBRARY_INSTALL_PATH})

	install(DIRECTORY include/EC3D
			DESTINATION include)
endif()
