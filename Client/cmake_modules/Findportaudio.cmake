find_path(Portaudio_INCLUDE_DIR NAMES portaudio.h PATHS ${PROJECT_SOURCE_DIR}/include)
find_library(Portaudio_LIBRARY NAMES portaudio PATHS ${PROJECT_SOURCE_DIR}/lib)