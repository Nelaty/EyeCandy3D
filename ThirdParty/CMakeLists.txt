if(NOT TARGET freetype)
    message("Thirdparty: Adding 'freetype'")
    
    set(FT_DISABLE_ZLIB OFF)
    set(FT_DISABLE_BZIP2 OFF)
    set(FT_DISABLE_PNG OFF)
    set(FT_DISABLE_HARFBUZZ OFF)
    set(FT_DISABLE_BROTLI OFF)
    set(FT_ENABLE_ERROR_STRINGS OFF)
  
    add_subdirectory(freetype)
endif()