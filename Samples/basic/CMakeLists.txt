# Configure name
set(EC_SAMPLE_NAME "basic")
set(EC_SAMPLE_FULL_NAME "${EYECANDY3D_SAMPLE_PREFIX}${EC_SAMPLE_NAME}")

# Build
add_executable(${EC_SAMPLE_FULL_NAME}
    main.cpp

    ExampleScene.cpp
    ExampleWindow.cpp
)
add_dependencies(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})
target_link_libraries(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})

# Install
add_custom_command(
		TARGET ${EC_SAMPLE_FULL_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/Samples/basic/res_basic/
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res_basic/)
