TEMPLATE        =       Client
TARGET          =       babel
QT              +=      core widgets gui network
CONFIG			+=		console

DESTDIR         =       build
OBJECTS_DIR     =       build/obj
MOC_DIR         =       build/moc
UI_DIR          =       build/ui
RCC_DIR         =       build/rcc

# win32:RC_ICONS 			+= 		resources/babel.ico
# ICON 						= 		resources/babel.svg

win32:QMAKE_CXXFLAGS		+=	-Wall -W -Werror /MP
unix:QMAKE_CXXFLAGS			+=	-Wall -W -Werror -std=c++14 -Wno-write-strings

INCLUDEPATH     +=      .												\
						includes										\
						includes/Network								\
						includes/Audio									\
						includes/Mutex									\
						includes/GUI									\
						includes/ServerCommunication					\
						includes/Commands								\
						dependencies/includes							\
						build											\
						build/ui										\
						build/moc

HEADERS         +=      includes/Network/IClientSocket.hpp                  \
						includes/Network/IServerSocket.hpp                  \
						includes/Mutex/IMutex.hpp							\
						includes/Network/SocketException.hpp    			\


HEADERS		+=	dependencies/includes/portaudio.h

SOURCES		+= 				sources/main.cpp                        						\
							sources/Network/SocketException.cpp     						\
							sources/Network/TcpClient.cpp           						\
							sources/Network/UdpClient.cpp									\
							sources/Mutex/ScopedLock.cpp									\
							

FORMS		+=			forms/BabelDialog.ui				\
						forms/BabelFlyer.ui					\
						forms/BabelInscription.ui			\
						forms/BabelSetting.ui				\
						forms/BabelMain.ui					\
						forms/BabelUpdate.ui

RESOURCES	+=			resources/BabelMainWindow.qrc		\
						resources/BabelMain.qrc

win32:LIBS	+=			-ldependencies/libs/portaudio_x86	\
						-ldependencies/libs/celt 			\
						-ldependencies/libs/opus 			\
						-ldependencies/libs/silk_common 	\
						-ldependencies/libs/silk_fixed		\
						-ldependencies/libs/silk_float

unix:LIBS	+=			-Ldependencies -lopus       \
						-Ldependencies -lportaudio