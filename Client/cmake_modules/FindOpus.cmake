find_path(Opus_INCLUDE_DIR NAMES opus.h PATHS ${PROJECT_SOURCE_DIR}/include)
find_library(Opus_LIBRARY NAMES opus PATHS ${PROJECT_SOURCE_DIR}/lib)
if (NOT Opus_LIBRARY)
    set(Opus_LIBRARY ${PROJECT_SOURCE_DIR}/lib/opus)
endif()
if (NOT Opus_INCLUDE_DIR)
    set(Opus_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/opus.h)
endif()