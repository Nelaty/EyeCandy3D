add_executable(${PROJECT_NAME}_Example
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleGui.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleScene.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/ExampleWindow.cpp
)

set_property(TARGET ${PROJECT_NAME}_Example PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME}_Example PROPERTY CXX_STANDARD 14)


add_dependencies(${PROJECT_NAME}_Example ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})

