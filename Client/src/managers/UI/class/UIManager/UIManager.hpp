#ifndef BABEL_UIMANAGER_HPP_
# define BABEL_UIMANAGER_HPP_

#include <unordered_map>
#include <memory>
#include <list>
#include <array>
#include <QApplication>
#include "Status.hpp"
#include "addcontactdiag.h"
#include "addtoconversationdiag.h"
#include "customnotificationdiag.h"
#include "logindiag.h"
#include "mainwindow.h"
#include "receivecalldiag.h"
#include "signupdiag.h"
#include "join.hpp"

namespace babel {
	class BabelClientManager;
}

namespace babel {
	class UIManager
    {
        public:
            enum class ContactInfoType : int
            {
                ONLINE = 0,
                CALLING_WAIT = 1,
                IN_CONVERSATION,
                IN_CALL,
                NO_CONTACT_SELECTED
            };

		public:        
			UIManager(babel::BabelClientManager&);
            ~UIManager();

            babel::Status const                                         showWindow(std::string const& windowName);
            babel::Status const                                         hideWindow(std::string const& windowName);

            babel::Status const                                         start();

            //AddContactDiag methods
            babel::Status const                                         addContactToFriendsList(std::string const& contactName);
            babel::Status const                                         closeContactWindow();

            //AddToConversationDiag methods
            babel::Status const                                         refreshCurrentlySelectedLabel(std::vector<std::string> const& listSelected);
            babel::Status const                                         refreshNewDataConversation(std::vector<std::string> const& newConversationList);

            //LoginDiag methods
            babel::Status const                                         saveNicknameFromLoginToSignupDiag(std::string const& nickname);

            //MainWindow methods
            babel::Status const                                         refreshGeneralInformations();
            babel::Status const                                         updateFriendsListConversations();
            babel::Status const                                         refreshSelectedContact(std::string const& selectedContact, babel::UIManager::ContactInfoType const type);
            babel::Status const                                         startCall();
            babel::Status const                                         hangupCall();
            babel::Status const                                         selectedFriendClicked(std::string const& contactName);

            //SignupDiag methods
            babel::Status const                                         saveNicknameFromSignupToLoginDiag(std::string const& nickname);

            //Miscellanous methods
            babel::Status const                                         showErrorDialog(std::string const& dataText);

            //Setters
            void                                                        setNickname(std::string const& nickname);
            void                                                        setFriendsOnline(uint32_t const friendsOnline);
            void                                                        setConversationList(std::list<std::string> const& vStr);

            void                                                        appendToConversationList(std::string const& nickname);
            void                                                        removeToConversationlist(std::string const& nickname);
            void                                                        clearConversationList();

            //Getters
            babel::BabelClientManager                                   &getRoot();
            babel::BabelClientManager const                             &getRoot() const;

		private:
            babel::BabelClientManager                                   &_root;
            std::unordered_map<std::string, std::shared_ptr<QWidget>>   _windowList;

            QString                                                     _nickname;
            quint32                                                     _friendsOnline;
            QList<std::string>                                          _conversationList;
	};
}

#endif // !BABEL_UIMANAGER_HPP_
