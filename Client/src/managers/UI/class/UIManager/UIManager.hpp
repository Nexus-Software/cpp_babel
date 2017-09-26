#ifndef BABEL_UIMANAGER_HPP_
# define BABEL_UIMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <QApplication>
#include "Status.hpp"
#include "addcontactdiag.h"
#include "customnotificationdiag.h"
#include "logindiag.h"
#include "mainwindow.h"
#include "receivecalldiag.h"
#include "signupdiag.h"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class UIManager
	{
		public:
			UIManager(babel::BabelClientManager&);
            ~UIManager();

            babel::Status const                                         showWindow(QString const& windowName);
            babel::Status const                                         hideWindow(QString const& windowName);

            babel::Status const                                         start();

            //AddContactDiag methods
            babel::Status const                                         addContactToFriendsList(QString const& contactName);

            //LoginDiag methods
            babel::Status const                                         saveNicknameFromLoginToSignupDiag(QString const& nickname);

            //MainWindow methods
            babel::Status const                                         refreshGeneralInformations();

            //SignupDiag methods
            babel::Status const                                         saveNicknameFromSignupToLoginDiag(QString const& nickname);

            //Miscellanous methods
            babel::Status const                                         showErrorDialog(QString const& dataText);

            void                                                        setNickname(QString const& nickname);
            void                                                        setFriendsOnline(quint32 const& friendsOnline);

            babel::BabelClientManager                                   &getRoot();
            babel::BabelClientManager const                             &getRoot() const;

		private:
            babel::BabelClientManager                                   &_root;
            std::unordered_map<std::string, std::shared_ptr<QWidget>>   _windowList;
            QString                                                     _nickname;
            quint32                                                     _friendsOnline;
	};
}

#endif // !BABEL_UIMANAGER_HPP_
