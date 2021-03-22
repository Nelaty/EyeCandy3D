file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.hpp" "*.h")
file(GLOB_RECURSE inline_files "*.inl")

set(all_source_files ${source_files} ${header_files} ${inline_files})

include_directories(include)

add_executable(${EYECANDY3D_TEST_NAME} ${all_source_files})
target_link_libraries(${EYECANDY3D_TEST_NAME}
        ${EYECANDY3D_ALL_DEPENDENCIES})

add_custom_command(
        TARGET ${EYECANDY3D_TEST_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Test/TestResources/
        ${CMAKE_BINARY_DIR}/bin/TestResources/)