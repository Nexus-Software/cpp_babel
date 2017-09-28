# GENERAL SETTINGS
cmake_minimum_required(VERSION 3.5)
project(babel)

set(APP_DIR ./)

include_directories(
	# NETWORK
	${APP_DIR}/src/network/interface/
	${APP_DIR}/src/network/class/QNetworkTcpClient/
    # DIALOG
    ${APP_DIR}/src/widget/class/AddContactDiag/
    ${APP_DIR}/src/widget/class/AddToConversationDiag/
    ${APP_DIR}/src/widget/class/CustomNotificationDiag/
    ${APP_DIR}/src/widget/class/LoginDiag/
    ${APP_DIR}/src/widget/class/MainWindow/
    ${APP_DIR}/src/widget/class/ReceiveCallDiag/
    ${APP_DIR}/src/widget/class/SignupDiag/
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
	# ---> AUDIO
	${APP_DIR}/src/standalone/class/Audio/
	# ---> CALL
	${APP_DIR}/src/standalone/class/Call
        # ---> CONTACT
        ${APP_DIR}/src/standalone/class/Contact
        # --> JOIN
        ${APP_DIR}/src/standalone/class/Join
        # ---> STATUS
	${APP_DIR}/src/standalone/class/Status
	# --> ERROR
	${APP_DIR}/src/standalone/class/Error/
	# --> LIB
	${APP_DIR}/include/
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Running moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
# APP TARGET
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

# AUDIO COMPONENTS
find_package(Portaudio REQUIRED)
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
    src/widget/class/LoginDiag/logindiag.ui
    src/widget/class/MainWindow/mainwindow.ui
    src/widget/class/ReceiveCallDiag/receivecalldiag.ui
    src/widget/class/SignupDiag/signupdiag.ui
    src/widget/class/AddContactDiag/addcontactdiag.ui
    src/widget/class/CustomNotificationDiag/customnotificationdiag.ui
    src/widget/class/AddToConversationDiag/addtoconversationdiag.ui
)

# EXECUTABLE
add_executable(babel_client ${SOURCE_CLIENT_FILES} ${HEADER_CLIENT_FILES_H} ${HEADER_CLIENT_FILES_HPP} ${SOURCE_CLIENT_FILES_H} ${SOURCE_CLIENT_FILES_HPP} ${UIS_HDRS})
# LIBRARIES
target_link_libraries(babel_client Qt5::Network Qt5::Widgets)
target_link_libraries(babel_client ${Portaudio_LIBRARY})

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
