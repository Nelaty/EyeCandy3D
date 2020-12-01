set(sources main.cpp)

# Configure name
set(EC_SAMPLE_NAME "geometry")
set(EC_SAMPLE_FULL_NAME "${EYECANDY3D_SAMPLE_PREFIX}${EC_SAMPLE_NAME}")

# Build
add_executable(${EC_SAMPLE_FULL_NAME} ${sources})
add_dependencies(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})
target_link_libraries(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})

# Install