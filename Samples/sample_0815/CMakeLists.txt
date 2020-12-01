file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.hpp" "*.h")
file(GLOB_RECURSE inline_files "*.inl")

set(all_source_files
		${source_files}
		${header_files}
		${inline_files})

# Configure name
set(EC_SAMPLE_NAME "0815")
set(EC_SAMPLE_FULL_NAME "${EYECANDY3D_SAMPLE_PREFIX}${EC_SAMPLE_NAME}")

# Build
add_executable(${EC_SAMPLE_FULL_NAME} ${all_source_files})
add_dependencies(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})
target_link_libraries(${EC_SAMPLE_FULL_NAME} ${PROJECT_NAME})

# Install
add_custom_command(
		TARGET ${EC_SAMPLE_FULL_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/Samples/sample_0815/res_sample_0815/
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res_sample_0815/)