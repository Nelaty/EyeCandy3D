file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx" "*.cc")
file(GLOB_RECURSE header_files "*.hpp" "*.h" "*.hxx")
file(GLOB_RECURSE inline_files "*.inl")

set(all_target_files
        ${source_files}
        ${header_files}
        ${inline_files})

add_library(${PROJECT_NAME} STATIC ${all_target_files})

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        opengl32
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
        glm

        SimpleIni
)
target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Install resources
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources/
        ${CMAKE_BINARY_DIR}/bin/Resources/)
