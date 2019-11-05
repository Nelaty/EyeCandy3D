cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project("EyeCandy3D")

enable_testing()



add_subdirectory(EyeCandy3D/src)
add_subdirectory(External)

add_subdirectory(Example)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC /usr/include/freetype2)




set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set_property(TARGET ${PROJECT_NAME} PROPERTY EyeCandy3D-warnings "-Wall")
endif()
if(NOT ${PROJECT_NAME}_CONFIGURED_ONCE)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_C_FLAGS "${EyeCandy3D-warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_CXX_FLAGS "${EyeCandy3D-warnings}" CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()




set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set_property(TARGET ${PROJECT_NAME} PROPERTY CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(${PROJECT_NAME}_CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")

