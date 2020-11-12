cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("EyeCandy3D")
set(PROJECT_SHORT_NAME "EC3D")

enable_testing()

#set(CMAKE_CXX_STANDARD 20)

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
include_directories(/usr/include/freetype2)

# Configure output paths
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all header files
file(GLOB_RECURSE header_files "${CMAKE_SOURCE_DIR}/EyeCandy3D/include/*" "${CMAKE_SOURCE_DIR}/External/include/*")


#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${header_files}")# ${CMAKE_SOURCE_DIR}/External/include/")

# Build project
add_subdirectory(EyeCandy3D/src)
install(TARGETS ${PROJECT_NAME}
		LIBRARY	DESTINATION lib)

add_subdirectory(External)
add_subdirectory(Example)


set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")

