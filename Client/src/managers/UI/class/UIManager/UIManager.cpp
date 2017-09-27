#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager(babel::BabelClientManager& ancestor)
:
    _root(ancestor),
    _windowList({
        {"AddContactDiag", std::make_shared<AddContactDiag>(nullptr, *this)},
        {"CustomNotificationDiag", std::make_shared<CustomNotificationDiag>(nullptr, *this)},
        {"LoginDiag", std::make_shared<LoginDiag>(nullptr, *this)},
        {"MainWindow", std::make_shared<MainWindow>(nullptr, *this)},
        {"ReceiveCallDiag", std::make_shared<ReceiveCallDiag>(nullptr, *this)},
        {"SignupDiag", std::make_shared<SignupDiag>(nullptr, *this)}
    }),
    _nickname("Anonymous"),
    _friendsOnline(0)
{
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}

babel::Status const                                                 babel::UIManager::showWindow(std::string const& windowName)
{
    if (!this->_windowList[windowName])
        return (babel::Status(1, "Window '" + windowName + "' couldn't be showed"));
    this->_windowList[windowName]->show();
    return (babel::Status(0, "Window '" + windowName + "' is now showed"));
}

babel::Status const                                                 babel::UIManager::hideWindow(std::string const& windowName)
{
    if (!this->_windowList[windowName])
        return (babel::Status(1, "Window '" + windowName + "' couldn't be showed"));
    this->_windowList[windowName]->hide();
    return (babel::Status(0, "Window '" + windowName + "' is now hidden"));
}

babel::Status const                                                 babel::UIManager::start()
{
    this->showWindow("LoginDiag");
    return (babel::Status(0, "UIManager 'start()' worked without error"));
}

babel::Status const                                                 babel::UIManager::addContactToFriendsList(std::string const& contactName)
{
    QListWidget *friendsList = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getFriendsList();

    // Asks the server to check if the user does really exists
    // v Temporary not adding duplicated names v
    if (!friendsList)
        return (babel::Status(1, "UIManager 'addContactToFriendsList()': friendsList was null"));
    else
    {
        if (friendsList->count() == 50)
            this->showErrorDialog("The friends limit has been reached (50).");
        else if (contactName.length() &&
            !friendsList->findItems(QString::fromStdString(contactName), Qt::MatchExactly).count())
          friendsList->addItem(QString::fromStdString(contactName));
    }
    return (babel::Status(0, "UIManager 'addContactToFriendsList()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromLoginToSignupDiag(std::string const& nickname)
{
    dynamic_cast<SignupDiag *>(this->_windowList["SignupDiag"].get())->getNicknameField()->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromLoginToSignupDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshGeneralInformations()
{
    dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getGeneralInformations()->setText("<html><head/><body><p><span style=\" font-size:10pt;\">Welcome\
                                                                                                          </span><span style=\" font-size:10pt; font-weight:600;\">" + this->_nickname + "</span><span style=\"\
                                                                                                          font-size:10pt;\"> !</span></p><p><span style=\" font-size:10pt;\">There are </span><span style=\"\
                                                                                                          font-size:10pt; font-weight:600;\">" + QString::number(this->_friendsOnline) + "</span><span style=\" font-size:10pt;\">\
                                                                                                          friends connected.</span></p></body></html>");
    return (babel::Status(0, "UIManager 'changeNicknameGeneralInformations()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromSignupToLoginDiag(std::string const& nickname)
{
    dynamic_cast<LoginDiag *>(this->_windowList["LoginDiag"].get())->getNicknameField()->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromSignupToLoginDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::showErrorDialog(std::string const& dataText)
{
    dynamic_cast<CustomNotificationDiag *>(this->_windowList["CustomNotificationDiag"].get())->setDataText(QString::fromStdString(dataText));
    this->showWindow("CustomNotificationDiag");
    return (babel::Status(0, "UIManager 'showErrorDialog()' worked without error"));
}

void                                                                babel::UIManager::setNickname(std::string const& nickname)
{
    this->_nickname = QString::fromStdString(nickname);
}

void                                                                babel::UIManager::setFriendsOnline(uint32_t const friendsOnline)
{
    this->_friendsOnline = friendsOnline;
}

babel::BabelClientManager                                           &babel::UIManager::getRoot()
{
    return (this->_root);
}

babel::BabelClientManager const                                     &babel::UIManager::getRoot() const
{
    return (this->_root);
}
