cmake_minimum_required(VERSION 3.8.1)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project("EyeCandy3D")
set(PROJECT_SHORT_NAME "EC3D")


set(CMAKE_CXX_STANDARD 20)

# Configure install paths
set(EYECANDY3D_INCLUDE_DIRECTORY EyeCandy3D/include/)
set(EYECANDY3D_LIBRARY_INSTALL_PATH lib)
set(EYECANDY3D_INCLUDE_INSTALL_PATH include/)

# Configure output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EYECANDY3D_TEST_NAME "Test")

# Build configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
	SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()
SET(CMAKE_DEBUG_POSTFIX "d")

# Compiler options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(warnings "-Wall -Wextra -Werror	\
	-Wno-error=unused-parameter \
	-Wno-error=unused-variable \
	-Wno-error=type-limits \
	-Wno-error=return-local-addr \
	-Wno-error=unused-function \
	-Wno-error=unused-but-set-variable \
	-Wno-error=implicit-fallthrough \
	-Wno-error=misleading-indentation \
	-std=c++20")
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# 	set(warnings "/W4 /WX /EHsc")
endif()
if(NOT CONFIGURED_ONCE)
	set(CMAKE_C_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
	set(CMAKE_CXX_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

# Find packages
find_package(Freetype REQUIRED)


include_directories(${FREETYPE_INCLUDE_DIRS}
		EyeCandy3D/include
		External/include)

# Build project
add_subdirectory(EyeCandy3D)
add_subdirectory(Example)

enable_testing()
add_subdirectory(Test)


add_test(NAME EyeCandy3DLibraryTest
		COMMAND ${EYECANDY3D_TEST_NAME} --config $<CONFIGURATION>
		--exe $<TARGET_FILE:${EYECANDY3D_TEST_NAME}>)

# Install library and header files
install(TARGETS ${PROJECT_NAME}
		LIBRARY	DESTINATION ${EYECANDY3D_LIBRARY_INSTALL_PATH})

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")

