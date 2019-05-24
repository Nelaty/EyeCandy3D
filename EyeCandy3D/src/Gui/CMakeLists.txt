target_sources(${PROJECT_NAME}
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/GuiPrimitiveRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GuiRenderer.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/GuiSystem.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/MiniAgui.cpp
)

add_subdirectory(Backend)
add_subdirectory(Listener)

