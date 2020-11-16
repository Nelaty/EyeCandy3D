file(GLOB_RECURSE source_files "*.cpp" "*.c" "*.cxx")
file(GLOB_RECURSE header_files "*.hpp" "*.h")
file(GLOB_RECURSE inline_files "*.inl")

set(all_source_files
		${source_files}
		${header_files}
		${inline_files})


add_executable(${PROJECT_NAME}_Example ${all_source_files})

add_custom_command(
		TARGET ${PROJECT_NAME}_Example POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/Resources/
		${CMAKE_CURRENT_BINARY_DIR}/Resources/)

add_dependencies(${PROJECT_NAME}_Example ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_Example ${PROJECT_NAME})