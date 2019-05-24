add_executable(${PROJECT_NAME}_Example
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleGui.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleScene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleWindow.cpp
)


add_dependencies(${PROJECT_NAME}_Example ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

