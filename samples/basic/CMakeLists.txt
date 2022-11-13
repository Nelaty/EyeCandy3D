# Configure name
set(EC_SAMPLE_NAME "basic")
set(EC_SAMPLE_FULL_NAME "${EYECANDY3D_SAMPLE_PREFIX}${EC_SAMPLE_NAME}")

# Build
add_executable(${EC_SAMPLE_FULL_NAME}
    main.cpp

    example-scene.cpp
    example-window.cpp
)
add_dependencies(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})
target_link_libraries(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})

# Install
ec3_install_resources(${EC_SAMPLE_FULL_NAME} ${CMAKE_CURRENT_BINARY_DIR}/Resources/)

add_custom_command(
		TARGET ${EC_SAMPLE_FULL_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/samples/basic/res_basic/
		${CMAKE_CURRENT_BINARY_DIR}/res_basic/)
