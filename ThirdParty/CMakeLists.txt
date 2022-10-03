###############################################################################
# freetype
###############################################################################
if(NOT TARGET freetype)
    message("ThirdParty: Adding 'freetype'")
    
    set(FT_DISABLE_ZLIB OFF)
    set(FT_DISABLE_BZIP2 OFF)
    set(FT_DISABLE_PNG OFF)
    set(FT_DISABLE_HARFBUZZ OFF)
    set(FT_DISABLE_BROTLI OFF)
    set(FT_ENABLE_ERROR_STRINGS OFF)
  
   # add_subdirectory(freetype)
endif()

###############################################################################
# glew-cmake
###############################################################################
if(NOT TARGET glew)
    message("ThirdParty: Adding 'glew-cmake'")
    add_subdirectory(glew-cmake)
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