cmake_minimum_required(VERSION 3.5)
project(Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)


# INCLUDES
include_directories(src)

# APP SRCS
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

set(Boost_USE_STATIC_LIBS   OFF)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.57.0 COMPONENTS system filesystem thread REQUIRED)

if(NOT Boost_FOUND)
    message("Boost >= 1.57.0 is needed for build")
    return()
endif()


message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

include_directories(${Boost_INCLUDE_DIRS})


add_executable(Server ${SOURCE_FILES})

target_compile_definitions(Server PRIVATE -DBOOST_ALL_NO_LIB -DBOOST_ALL_DYN_LINK)
target_link_libraries(Server ${Boost_LIBRARIES})
