cmake_minimum_required(VERSION 3.14)
project(SimpleIni)

set(CXX_STANDARD 20)
add_library(SimpleIni STATIC
    SimpleIni.cpp
)
target_include_directories(SimpleIni PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)