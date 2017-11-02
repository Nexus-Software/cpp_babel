find_path(Opus_INCLUDE_DIR NAMES opus.h PATHS ${PROJECT_SOURCE_DIR}/include)
find_library(Opus_LIBRARY NAMES opus.lib PATHS ${PROJECT_SOURCE_DIR}/lib)