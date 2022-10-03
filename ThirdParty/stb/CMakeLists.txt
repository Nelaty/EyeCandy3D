cmake_minimum_required(VERSION 3.14)
project(stb)

set(CMAKE_CXX_STANDARD 20)
add_library(stb INTERFACE)
target_include_directories(stb 
    INTERFACE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

