project(SimpleIni)

set(CXX_STANDARD 20)
add_library(SimpleIni STATIC
    SimpleIni.cpp
)
target_include_directories(SimpleIni PUBLIC SimpleIni.h)