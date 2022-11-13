add_library(${PROJECT_NAME} STATIC 
    src/application.cpp
    src/cursor.cpp
    src/frame.cpp
    src/node.cpp
    src/scene.cpp
    src/scene-renderer.cpp
    src/scene-system.cpp
    src/transform-3d.cpp

    src/common/config.cpp
    src/common/initializer.cpp
    src/common/logging.cpp

    src/graphics/camera.cpp
    src/graphics/camera-controller.cpp
    src/graphics/drawable.cpp
    src/graphics/geometry/circle-geometry.cpp
    src/graphics/geometry/cube-geometry.cpp
    src/graphics/geometry/cylinder-geometry.cpp
    src/graphics/geometry/dynamic-geometry.cpp
    src/graphics/geometry/dynamic-line-geometry.cpp
    src/graphics/geometry/geometry.cpp
    src/graphics/geometry/geometry-data.cpp
    src/graphics/geometry/geometry-access.cpp
    src/graphics/geometry/line-geometry.cpp
    src/graphics/geometry/line-geometry-factory.cpp
    src/graphics/geometry/linestrip-geometry.cpp
    src/graphics/geometry/rectangle-geometry.cpp
    src/graphics/geometry/sphere-geometry.cpp
    src/graphics/geometry/spring-geometry.cpp
    src/graphics/geometry/static-geometry.cpp
    src/graphics/lighting/directional-light.cpp
    src/graphics/lighting/light.cpp
    src/graphics/lighting/light-system.cpp
    src/graphics/lighting/omni-light.cpp
    src/graphics/lighting/point-light.cpp
    src/graphics/lighting/spot-light.cpp
    src/graphics/material/material.cpp
    src/graphics/material/texture.cpp
    src/graphics/render/renderer.cpp
    src/graphics/shader/shader.cpp
    src/graphics/shader/shader-manager.cpp
    src/graphics/shader/shader-timed.cpp
    src/graphics/text/font-texture-atlas.cpp
    src/graphics/text/freetype.cpp

    #src/Gui/GuiPrimitiveRenderer.cpp
    #src/Gui/GuiRenderer.cpp
    #src/Gui/GuiSystem.cpp
    #src/Gui/MiniAgui.cpp
    #src/Gui/Backend/OpenGLCursorProvider.cpp
    #src/Gui/Backend/OpenGLFont.cpp
    #src/Gui/Backend/OpenGLFontLoader.cpp
    #src/Gui/Backend/OpenGLGraphics.cpp
    #src/Gui/Backend/OpenGLImage.cpp
    #src/Gui/Backend/OpenGLImageLoader.cpp
    #src/Gui/Backend/OpenGLInput.cpp
    #src/Gui/Listener/GenericActionListener.cpp
    #src/Gui/Listener/GenericButtonListener.cpp
    #src/Gui/Listener/GenericCheckBoxListener.cpp
    #src/Gui/Listener/GenericDropDownListener.cpp
    #src/Gui/Listener/GenericFrameListener.cpp
    #src/Gui/Listener/GenericHScrollBarListener.cpp
    #src/Gui/Listener/GenericLabelListener.cpp
    #src/Gui/Listener/GenericListBoxListener.cpp
    #src/Gui/Listener/GenericRadioButtonListener.cpp
    #src/Gui/Listener/GenericSliderListener.cpp
    #src/Gui/Listener/GenericTabbedPaneListener.cpp
    #src/Gui/Listener/GenericTextBoxListener.cpp
    #src/Gui/Listener/GenericTextFieldListener.cpp
    #src/Gui/Listener/GenericVScrollBarListener.cpp
    #src/Gui/Listener/GenericWidgetListener.cpp

    src/input/device-registry.cpp
    src/input/event-system.cpp
    src/input/input-event.cpp
    src/input/input-listener.cpp
    src/input/input-observable.cpp
    src/input/keyboard.cpp
    src/input/mouse.cpp
    src/input/scene-controller.cpp

    src/utilities/profiler.cpp
    src/utilities/random.cpp
    src/utilities/timer.cpp

    src/window/viewport.cpp
    src/window/window.cpp
    src/window/window-callbacks.cpp
    src/window/window-creation-hints.cpp
)

find_package(OpenGL REQUIRED)
message("------------ OpenGL libraries ------------")
message("GL found: ${OPENGL_FOUND}")
message("GLU found: ${OPENGL_GLU_FOUND}")
message("GLX found: ${OPENGL_GLX_FOUND}")
message("Libraries: ${OPENGL_LIBRARIES}")
message("------------------------------------------")


target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        ${OPENGL_LIBRARIES}
        #agui
        glfw
        freetype

        glm
        libglew_static
        SimpleIni
        spdlog::spdlog
        stb
)

target_include_directories(${PROJECT_NAME} 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

ec3_install_resources(${PROJECT_NAME} 
    ${CMAKE_CURRENT_BINARY_DIR}/bin/Resources/
)
