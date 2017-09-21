# GENERAL SETTINGS
cmake_minimum_required(VERSION 3.6)
project(babel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_DIR ./)

# Running moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# APP TARGET
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win32)
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake_modules)

# AUDIO COMPONENTS
# find_package(PortAudio)
# find_package(Opus)

# QT COMPONENTS
find_package(Qt5Network REQUIRED)
find_package(Qt5Widgets REQUIRED)

# QT INCLUDES
include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

# INCLUDES
include_directories(${APP_DIR}/src)

# APP SRCS
file(GLOB_RECURSE SOURCE_CLIENT_FILES		${APP_DIR}/src/*.cpp)
file(GLOB_RECURSE SOURCE_CLIENT_FILES_HPP	${APP_DIR}/src/*.hpp)

# APP HEADERS
file(GLOB_RECURSE HEADER_CLIENT_FILES_H		${APP_DIR}/include/*.h)
file(GLOB_RECURSE HEADER_CLIENT_FILES_HPP	${APP_DIR}/include/*.hpp)

# APP FORMS UI
qt5_wrap_ui(UIS_HDRS
    src/dialog/logindiag.ui
    src/dialog/mainwindow.ui
    src/dialog/receivecalldiag.ui
    src/dialog/signupdiag.ui
)

# EXECUTABLE
add_executable(babel_client ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES_H} ${HEADER_CLIENT_FILES_HPP} ${SOURCE_CLIENT_FILES_HPP} ${UIS_HDRS})
# LIBRARIES
target_link_libraries(babel_client Qt5::Network Qt5::Widgets)


# PROPER GUI WITHOUT CONSOLE [ALL OS] // DO NOT TOUCH
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)