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

            babel::Status const                                         showWindow(std::string const& windowName);
            babel::Status const                                         hideWindow(std::string const& windowName);

            babel::Status const                                         start();

            //AddContactDiag methods
            babel::Status const                                         addContactToFriendsList(std::string const& contactName);

            //LoginDiag methods
            babel::Status const                                         saveNicknameFromLoginToSignupDiag(std::string const& nickname);

            //MainWindow methods
            babel::Status const                                         refreshGeneralInformations();

            //SignupDiag methods
            babel::Status const                                         saveNicknameFromSignupToLoginDiag(std::string const& nickname);

            //Miscellanous methods
            babel::Status const                                         showErrorDialog(std::string const& dataText);

            void                                                        setNickname(std::string const& nickname);
            void                                                        setFriendsOnline(uint32_t const friendsOnline);

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
