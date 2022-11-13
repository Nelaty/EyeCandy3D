function(ec3_install_dir TARGET_NAME SOURCE_DIR TARGET_DIR)
    add_custom_command(
            TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${SOURCE_DIR}
            ${TARGET_DIR}
    )
endfunction()

function(ec3_install_resources TARGET_NAME TARGET_DIR)
    ec3_install_dir(${TARGET_NAME} ${EYECANDY3D_DEFAULT_RESOURCE_DIR} ${TARGET_DIR})
endfunction()