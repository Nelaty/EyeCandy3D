
add_library(${PROJECT_NAME} STATIC 
    #src/Common/
    #src/Graphics/
    #src/Gui/
    #src/Input/
    #src/Utilities/
    #src/Window/

    src/Transform3D.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        opengl32
        #agui
        #glfw
        #GLU
        #GL
        #X11
        #Xrandr
        #Xinerama
        #Xi
        #Xxf86vm
        #Xcursor
        #pthread
        #dl
        #freetype

        glm
        #GLEW::glew_s
        SimpleIni
        spdlog::spdlog
        stb
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
