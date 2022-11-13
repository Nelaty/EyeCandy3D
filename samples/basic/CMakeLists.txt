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

# Install resource files
ec3_install_resources(${EC_SAMPLE_FULL_NAME} 
	${CMAKE_CURRENT_BINARY_DIR}/Resources/
)
ec3_install_dir(${EC_SAMPLE_FULL_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/res_basic/	
	${CMAKE_CURRENT_BINARY_DIR}/Resources/
)
