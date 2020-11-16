add_library(${PROJECT_NAME} STATIC
	Application.cpp
	Camera.cpp
	CameraController.cpp
	CircleGeometry.cpp
	CubeGeometry.cpp
	Cursor.cpp
	CylinderGeometry.cpp
	DeviceRegistry.cpp
	DirectionalLight.cpp
	Drawable.cpp
	DynamicGeometry.cpp
	DynamicLineGeometry.cpp
	EventSystem.cpp
	FontTextureAtlas.cpp
	Frame.cpp
	Freetype.cpp
	Geometry.cpp
	GeometryData.cpp
	IGeometryAccess.cpp
	InputEvent.cpp
	InputListener.cpp
	InputObservable.cpp
	Keyboard.cpp
	Light.cpp
	LightSystem.cpp
	LineGeometry.cpp
	LineGeometryFactory.cpp
	LineStripGeometry.cpp
	Material.cpp
	Mouse.cpp
	Node.cpp
	OmniLight.cpp
	PointLight.cpp
	RectangleGeometry.cpp
	Renderer.cpp
	Scene.cpp
	SceneController.cpp
	SceneRenderer.cpp
	SceneSystem.cpp
	SphereGeometry.cpp
	SpotLight.cpp
	SpringGeometry.cpp
	StaticGeometry.cpp
	Texture.cpp
	Transform3D.cpp
	Viewport.cpp
	Window.cpp
	WindowCreationHints.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/EyeCandy3D/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/External/include)


target_link_libraries(${PROJECT_NAME}
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


add_subdirectory(Shader)



