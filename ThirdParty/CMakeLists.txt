
###############################################################################
# glew-cmake
###############################################################################
if(NOT TARGET glew)
    message("ThirdParty: Adding 'glew-cmake'")
    add_subdirectory(glew-cmake)
endif()

###############################################################################
# glfw
###############################################################################
if(NOT TARGET glfw)
    message("ThirdParty: Adding 'glfw'")
    add_subdirectory(glfw)
endif()

###############################################################################
# glm
###############################################################################
if(NOT TARGET glm)
    message("ThirdParty: Adding glm")
    add_subdirectory(glm)
endif()

###############################################################################
# SimpleIni
###############################################################################
if(NOT TARGET SimpleIni)
    message("ThirdParty: Adding SimpleIni")
    add_subdirectory(SimpleIni)
endif()

###############################################################################
# spdlog
###############################################################################
if(NOT TARGET spdlog::splog)
    message("ThirdParty: Adding spdlog")
    add_subdirectory(spdlog)
endif()

###############################################################################
# stb
###############################################################################
if(NOT TARGET stb)
    message("ThirdParty: Adding stb libraries")
    add_subdirectory(stb)
endif()

###############################################################################
# freetype
###############################################################################
if(NOT TARGET freetype)
    message("ThirdParty: Adding 'freetype'")
    
    set(FT_DISABLE_ZLIB ON)
    set(FT_DISABLE_BZIP2 ON)
    set(FT_DISABLE_PNG ON)
    set(FT_DISABLE_HARFBUZZ ON)
    set(FT_DISABLE_BROTLI ON)
    set(FT_ENABLE_ERROR_STRINGS ON)
  
    add_subdirectory(freetype)
endif()