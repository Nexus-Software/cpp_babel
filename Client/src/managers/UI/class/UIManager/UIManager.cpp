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
    })
{
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}

babel::Status const                                                 babel::UIManager::showWindow(QString const& windowName)
{
    if (!this->_windowList[windowName.toStdString()])
        return (babel::Status(1, "Window '" + windowName.toStdString() + "' couldn't be showed"));
    this->_windowList[windowName.toStdString()]->show();
    return (babel::Status(0, "Window '" + windowName.toStdString() + "' is now showed"));
}

babel::Status const                                                 babel::UIManager::hideWindow(QString const& windowName)
{
    if (!this->_windowList[windowName.toStdString()])
        return (babel::Status(1, "Window '" + windowName.toStdString() + "' couldn't be showed"));
    this->_windowList[windowName.toStdString()]->hide();
    return (babel::Status(0, "Window '" + windowName.toStdString() + "' is now hidden"));
}

babel::Status const                                                 babel::UIManager::start()
{
    this->showWindow("LoginDiag");
    return (babel::Status(0, "UIManager 'start()' worked without error"));
}

babel::Status const                                                 babel::UIManager::addContactToFriendsList(QString const& contactName)
{
    QListWidget *friendsList = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getFriendsList();

    // Asks the server to check if the user does really exists
    // v Temporary not adding duplicated names v
    if (friendsList && contactName.length() &&
        !friendsList->findItems(contactName, Qt::MatchExactly).count())
        friendsList->addItem(contactName);
    return (babel::Status(0, "UIManager 'addContactToFriendsList()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromLoginToSignupDiag(const QString &nickname)
{
    dynamic_cast<SignupDiag *>(this->_windowList["SignupDiag"].get())->getNicknameField()->setText(nickname);
    return (babel::Status(0, "UIManager 'saveNicknameFromLoginToSignupDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromSignupToLoginDiag(QString const& nickname)
{
    dynamic_cast<LoginDiag *>(this->_windowList["LoginDiag"].get())->getNicknameField()->setText(nickname);
    return (babel::Status(0, "UIManager 'saveNicknameFromSignupToLoginDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::showErrorDialog(const QString &dataText)
{
    dynamic_cast<CustomNotificationDiag *>(this->_windowList["CustomNotificationDiag"].get())->setDataText(dataText);
    this->showWindow("CustomNotificationDiag");
    return (babel::Status(0, "UIManager 'showErrorDialog()' worked without error"));
}

babel::BabelClientManager                                           &babel::UIManager::getRoot()
{
    return (this->_root);
}

babel::BabelClientManager const                                     &babel::UIManager::getRoot() const
{
    return (this->_root);
}
