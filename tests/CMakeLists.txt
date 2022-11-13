add_executable(${PROJECT_NAME}_unittests 
    src/common/test-config.cpp
    src/common/vector-approx.cpp

    src/graphics/geometry/circle-geometry.cpp
    src/graphics/geometry/cube-geometry.cpp
    src/graphics/geometry/cylinder-geometry.cpp
    src/graphics/geometry/line-geometry.cpp
    src/graphics/geometry/rectangle-geometry.cpp
    src/graphics/geometry/sphere-geometry.cpp
    src/graphics/material/material-test.cpp
    
    src/main.cpp
)

target_include_directories(${PROJECT_NAME}_unittests 
    PUBLIC
        include
)
target_link_libraries(${PROJECT_NAME}_unittests
        ${PROJECT_NAME}
        ${EYECANDY3D_ALL_DEPENDENCIES})

# Add tests to CTest
add_test(${PROJECT_NAME}_unittests COMMAND 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_unittests
)
add_dependencies(CTest ${PROJECT_NAME}_unittests)

# Install resource files
ec3_install_dir(${PROJECT_NAME}_unittests
    ${CMAKE_CURRENT_SOURCE_DIR}/TestResources/
    ${CMAKE_CURRENT_BINARY_DIR}/TestResources/
)
