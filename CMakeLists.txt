cmake_minimum_required(VERSION 3.5.1)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)
project("EyeCandy3D")

enable_testing()

# Build configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
	SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()
SET(CMAKE_DEBUG_POSTFIX "d")

# Compiler options
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra -Werror \
	-Wno-error=unused-parameter \
	-Wno-error=unused-variable \
	-Wno-error=type-limits \
	-Wno-error=return-local-addr \
	-Wno-error=unused-function \
	-Wno-error=unused-but-set-variable \
	-Wno-error=implicit-fallthrough \
	-Wno-error=misleading-indentation \
	-std=c++14")
# elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
# 	set(warnings "/W4 /WX /EHsc")
endif()
if(NOT CONFIGURED_ONCE)
	set(CMAKE_C_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
	set(CMAKE_CXX_FLAGS "${warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

include_directories(/usr/include/freetype2)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Build project
add_subdirectory(EyeCandy3D/src)
add_subdirectory(External)
add_subdirectory(Example)

# Installation
install(TARGETS ${PROJECT_NAME}
		LIBRARY	DESTINATION lib)

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")

