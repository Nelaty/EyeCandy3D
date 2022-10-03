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
  
    add_subdirectory(freetype)
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
