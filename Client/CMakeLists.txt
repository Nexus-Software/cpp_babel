# GENERAL SETTINGS
cmake_minimum_required(VERSION 3.6)
project(babel)

set(APP_DIR ./)

include_directories(
    # DIALOG
    ${APP_DIR}/src/dialog/class/AddContactDiag/
    ${APP_DIR}/src/dialog/class/CustomNotificationDiag/
    ${APP_DIR}/src/dialog/class/LoginDiag/
    ${APP_DIR}/src/dialog/class/MainWindow/
    ${APP_DIR}/src/dialog/class/ReceiveCallDiag/
    ${APP_DIR}/src/dialog/class/SignupDiag/
	# MANAGERS
	# ---> CALL
	${APP_DIR}/src/managers/Call/class/CallManager/
	# ---> COMMUNICATION
	${APP_DIR}/src/managers/Communication/interface/ICommunication/
	${APP_DIR}/src/managers/Communication/class/AudioCommunication/
	${APP_DIR}/src/managers/Communication/class/TextCommunication/
	${APP_DIR}/src/managers/Communication/class/VideoCommunication/
	# ---> CONTACT
	${APP_DIR}/src/managers/Contact/class/ContactManager/
	# ---> CORE
	${APP_DIR}/src/managers/Core/class/BabelClientManager/
	# ---> MEDIA
	${APP_DIR}/src/managers/GlobalMediaManager/class/GlobalMediaManager/
	${APP_DIR}/src/managers/media/class/AudioManager/
	${APP_DIR}/src/managers/media/class/TextManager/
	${APP_DIR}/src/managers/media/class/VideoManager/
	${APP_DIR}/src/managers/media/interface/IMediaManager/
	# ---> NETWORK
	${APP_DIR}/src/managers/Network/class/NetworkManager/
	# ---> UI
	${APP_DIR}/src/managers/UI/class/UIManager/
	# STANDALONE
	# ---> CALL
	${APP_DIR}/src/standalone/class/Call
	# ---> CONTACT
	${APP_DIR}/src/standalone/class/Contact
    # ---> STATUS
	${APP_DIR}/src/standalone/class/Status
	# --> ERROR
	${APP_DIR}/src/standalone/class/Error
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Running moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# APP TARGET
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/win32)

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
file(GLOB_RECURSE SOURCE_CLIENT_FILES_H		${APP_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_CLIENT_FILES_HPP	${APP_DIR}/src/*.hpp)

# APP HEADERS
file(GLOB_RECURSE HEADER_CLIENT_FILES_H		${APP_DIR}/include/*.h)
file(GLOB_RECURSE HEADER_CLIENT_FILES_HPP	${APP_DIR}/include/*.hpp)

# APP FORMS UI
qt5_wrap_ui(UIS_HDRS
    src/dialog/class/LoginDiag/logindiag.ui
    src/dialog/class/MainWindow/mainwindow.ui
    src/dialog/class/ReceiveCallDiag/receivecalldiag.ui
    src/dialog/class/SignupDiag/signupdiag.ui
    src/dialog/class/AddContactDiag/addcontactdiag.ui
    src/dialog/class/CustomNotificationDiag/customnotificationdiag.ui
)

# EXECUTABLE
add_executable(babel_client ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES_H} ${HEADER_CLIENT_FILES_HPP} ${SOURCE_CLIENT_FILES_H} ${SOURCE_CLIENT_FILES_HPP} ${UIS_HDRS})
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
