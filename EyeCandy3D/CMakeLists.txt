file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.hpp" "*.h" "*.hxx")
file(GLOB_RECURSE inline_files "*.inl")

set(all_target_files
        ${source_files}
        ${header_files}
        ${inline_files})

add_library(${PROJECT_NAME} STATIC ${all_target_files})

#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/EyeCandy3D/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/External/include)

target_link_libraries(${PROJECT_NAME}
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
        freetype
        )



