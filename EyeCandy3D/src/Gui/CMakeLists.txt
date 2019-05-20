target_sources(${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GuiPrimitiveRenderer.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GuiRenderer.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/GuiSystem.cpp
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/MiniAgui.cpp
)

add_subdirectory(Backend)
add_subdirectory(Listener)

