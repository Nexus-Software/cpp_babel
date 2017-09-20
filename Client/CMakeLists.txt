cmake_minimum_required(VERSION 3.6)
project(babel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(SERVER_DIR ./server)
set(CLIENT_DIR ./)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")

# find_package(Boost COMPONENTS system thread REQUIRED)
# find_package(PortAudio)
# find_package(Opus)

## QT ##

# Qt components
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)

# include_directories(${Boost_INCLUDE_DIR})

# INCLUDES
include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
## QT ##

# include_directories(${SERVER_DIR}/src)
include_directories(${CLIENT_DIR}/src)

#SERVER FILES
# file(GLOB_RECURSE SOURCE_SERVER_FILES ${SERVER_DIR}/src/*.cc)
# file(GLOB_RECURSE HEADER_SERVER_FILES ${SERVER_DIR}/src/*.h)

#CLIENT FILES
file(GLOB_RECURSE SOURCE_CLIENT_FILES ${CLIENT_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADER_CLIENT_FILES ${CLIENT_DIR}/include/*.h)
qt5_wrap_ui(UIS_HDRS
    #src/QTSrcs/dialogreceivecall.ui
    src/QTSrcs/logindiag.ui
    src/QTSrcs/mainwindow.ui
    src/QTSrcs/receivecalldiag.ui
    src/QTSrcs/signupdiag.ui
)

#EXECUTABLE SERVER
# add_executable(babel_server ${SOURCE_SERVER_FILES} ${HEADER_SERVER_FILES})
# target_link_libraries(babel_server LINK_PUBLIC ${Boost_LIBRARIES})

#EXECUTABLE CLIENT
add_executable(babel_client ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES} ${UIS_HDRS})
target_link_libraries(babel_client Qt5::Network Qt5::Widgets)
