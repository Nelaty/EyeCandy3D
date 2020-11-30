set(sample_name "geometry")
set(sample_full_name "${EYECANDY3D_SAMPLE_PREFIX}${sample_name}")

set(sources main.cpp)


add_executable(${EYECANDY3D_SAMPLE_PREFIX}geometry ${sources})
add_dependencies(${sample_full_name} ${PROJECT_NAME})
target_link_libraries(${sample_full_name} ${PROJECT_NAME})