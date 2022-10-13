add_library(${PROJECT_NAME} STATIC 
    src/Application.cpp
    src/Cursor.cpp
    src/Frame.cpp
    src/Node.cpp
    src/Scene.cpp
    src/SceneRenderer.cpp
    src/SceneSystem.cpp
    src/Transform3D.cpp

    src/Common/Config.cpp
    src/Common/EyeCandy3dInitializer.cpp
    src/Common/Logging.cpp

    src/Graphics/Camera.cpp
    src/Graphics/CameraController.cpp
    src/Graphics/Drawable.cpp
    src/Graphics/Geometry/CircleGeometry.cpp
    src/Graphics/Geometry/CubeGeometry.cpp
    src/Graphics/Geometry/CylinderGeometry.cpp
    src/Graphics/Geometry/DynamicGeometry.cpp
    src/Graphics/Geometry/DynamicLineGeometry.cpp
    src/Graphics/Geometry/Geometry.cpp
    src/Graphics/Geometry/GeometryData.cpp
    src/Graphics/Geometry/IGeometryAccess.cpp
    src/Graphics/Geometry/LineGeometry.cpp
    src/Graphics/Geometry/LineGeometryFactory.cpp
    src/Graphics/Geometry/LineStripGeometry.cpp
    src/Graphics/Geometry/RectangleGeometry.cpp
    src/Graphics/Geometry/SphereGeometry.cpp
    src/Graphics/Geometry/SpringGeometry.cpp
    src/Graphics/Geometry/StaticGeometry.cpp
    src/Graphics/Lighting/DirectionalLight.cpp
    src/Graphics/Lighting/Light.cpp
    src/Graphics/Lighting/LightSystem.cpp
    src/Graphics/Lighting/OmniLight.cpp
    src/Graphics/Lighting/PointLight.cpp
    src/Graphics/Lighting/SpotLight.cpp
    src/Graphics/Material/Material.cpp
    src/Graphics/Material/Texture.cpp
    src/Graphics/Render/Renderer.cpp
    src/Graphics/Shader/Shader.cpp
    src/Graphics/Shader/ShaderManager.cpp
    src/Graphics/Shader/ShaderTimed.cpp
    src/Graphics/Text/FontTextureAtlas.cpp
    src/Graphics/Text/Freetype.cpp

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

    src/Input/DeviceRegistry.cpp
    src/Input/EventSystem.cpp
    src/Input/InputEvent.cpp
    src/Input/InputListener.cpp
    src/Input/InputObservable.cpp
    src/Input/Keyboard.cpp
    src/Input/Mouse.cpp
    src/Input/SceneController.cpp

    src/Utilities/Profiler.cpp
    src/Utilities/Random.cpp
    src/Utilities/Timer.cpp

    src/Window/Viewport.cpp
    src/Window/Window.cpp
    src/Window/WindowCallbacks.cpp
    src/Window/WindowCreationHints.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        opengl32
        #agui
        glfw
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

# Install resources
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources/
        ${CMAKE_BINARY_DIR}/bin/Resources/)
