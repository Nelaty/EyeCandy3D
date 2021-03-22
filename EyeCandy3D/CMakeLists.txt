# Set source files
file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx" "*.cc")
file(GLOB_RECURSE header_files "*.hpp" "*.h" "*.hxx")
file(GLOB_RECURSE inline_files "*.inl")

set(all_target_files
        ${source_files}
        ${header_files}
        ${inline_files})

add_library(${PROJECT_NAME} STATIC ${all_target_files})

#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/EyeCandy3D/include)
#target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/ThirdParty/include)

target_link_libraries(${PROJECT_NAME} ${EYECANDY3D_DEPENDENCIES})

# Install resources
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources/
        ${CMAKE_BINARY_DIR}/bin/Resources/)