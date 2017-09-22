cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)


# INCLUDES
include_directories(src)

# APP SRCS
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

find_package(Boost 1.57.0 COMPONENTS system filesystem thread REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_executable(Server ${SOURCE_FILES})

if(Boost_FOUND)

    target_link_libraries(Server ${Boost_LIBRARIES})
endif()