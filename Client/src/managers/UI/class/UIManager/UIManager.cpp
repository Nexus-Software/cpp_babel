#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager(babel::BabelClientManager& ancestor)
:
    _root(ancestor),
    _windowList({
        {"AddContactDiag", std::make_shared<AddContactDiag>(nullptr, *this)},
        {"AddToConversationDiag", std::make_shared<AddToConversationDiag>(nullptr, *this)},
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

babel::Status const                                                 babel::UIManager::refreshCurrentlySelectedLabel(std::vector<std::string> const& listSelected)
{
    QLabel                      *currentlySelectedLabel = dynamic_cast<AddToConversationDiag *>(this->_windowList["AddToConversationDiag"].get())->getCurrentlySelectedLabel();

    if (!listSelected.empty())
    {
        currentlySelectedLabel->setText("<html><head/><body><p>Currently selected:<span style=\" font-weight:600;\">");
        for (auto it : listSelected)
            currentlySelectedLabel->setText(currentlySelectedLabel->text() + " " + QString::fromStdString(it));
        currentlySelectedLabel->setText(currentlySelectedLabel->text() + "</span></p></body></html>");
    }
    else
        currentlySelectedLabel->setText("<html><head/><body><p>Currently selected: <span style=\" font-weight:600;\">None</span></p></body></html>");
    return (babel::Status(0, "UIManager 'refreshCurrentlySelectedLabel()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshNewDataConversation(std::vector<std::string> const& newConversationList)
{
    QListWidget *friendsList = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getFriendsList();
    QPushButton *messageSendButton = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getMessageSendButton();
    QLineEdit   *messageSendField = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getMessageSendField();
    QPushButton *callButton = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getCallButton();

    if (!friendsList || !messageSendButton || !messageSendField || !callButton)
        return (babel::Status(1, "UIManager 'refreshNewDataConversation()': A widget was null"));
    this->_conversationList = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(newConversationList));
    for (quint32 i = 0; i < friendsList->count(); i++)
    {
        if (this->_conversationList.length() != 1)
        {
            friendsList->item(i)->setSelected(false);
            if (this->_conversationList.isEmpty())
                this->refreshSelectedContact("", false);
            else
                this->refreshSelectedContact(utils::join(this->_conversationList.toVector().toStdVector(), ", "), true);
        }
        else
        {
            for (auto it : this->_conversationList)
            {
                if (friendsList->item(i)->data(0).toString().toStdString() == it)
                {
                    friendsList->item(i)->setSelected(true);
                    this->refreshSelectedContact(friendsList->item(i)->data(0).toString().toStdString(), false);
                }
                else
                    friendsList->item(i)->setSelected(false);
            }
        }
    }
    if (this->_conversationList.length() >= 1)
    {
        messageSendButton->setEnabled(true);
        messageSendField->setEnabled(true);
        callButton->setEnabled(true);
    }
    else
    {
        messageSendButton->setEnabled(false);
        messageSendField->setEnabled(false);
        callButton->setEnabled(false);
    }
    return (babel::Status(0, "UIManager 'refreshNewDataConversation()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromLoginToSignupDiag(std::string const& nickname)
{
    QLineEdit *nicknameField = dynamic_cast<SignupDiag *>(this->_windowList["SignupDiag"].get())->getNicknameField();

    if (!nicknameField)
        return (babel::Status(1, "UIManager 'saveNicknameFromLoginToSignupDiag()': The NicknameField widget was null"));
    nicknameField->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromLoginToSignupDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshGeneralInformations()
{
    QLabel *generalInformations = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getGeneralInformations();

    if (!generalInformations)
        return (babel::Status(1, "UIManager 'refreshGeneralInformations()': The GeneralInformations widget was null"));
    generalInformations->setText("<html><head/><body><p><span style=\" font-size:10pt;\">Welcome\
                                  </span><span style=\" font-size:10pt; font-weight:600;\">" + this->_nickname + "</span><span style=\"\
                                  font-size:10pt;\"> !</span></p><p><span style=\" font-size:10pt;\">There are </span><span style=\"\
                                  font-size:10pt; font-weight:600;\">" + QString::number(this->_friendsOnline) + "</span><span style=\" font-size:10pt;\">\
                                  friends connected.</span></p></body></html>");
    return (babel::Status(0, "UIManager 'changeNicknameGeneralInformations()' worked without error"));
}

babel::Status const                                                 babel::UIManager::updateFriendsListConversations()
{
    AddToConversationDiag       *addToConversationDiag = dynamic_cast<AddToConversationDiag *>(this->_windowList["AddToConversationDiag"].get());
    QListWidget                 *friendsListConversations = addToConversationDiag->getFriendsList();
    QListWidget                 *friendsListMainWin = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getFriendsList();
    QLabel                      *currentlySelectedLabel = addToConversationDiag->getCurrentlySelectedLabel();
    QList<QListWidgetItem *>    selectedFriend;

    if (!addToConversationDiag || !friendsListConversations || !friendsListMainWin || !currentlySelectedLabel)
        return (babel::Status(1, "UIManager 'updateFriendsListConversations()': A widget was null"));
    selectedFriend = friendsListMainWin->selectedItems();
    QList<std::string> &tmpConversationList = addToConversationDiag->getTmpConversationList();
    while (friendsListConversations->count())
        friendsListConversations->takeItem(0);
    tmpConversationList.clear();
    for (auto it : this->_conversationList)
        tmpConversationList.append(it);
    this->refreshCurrentlySelectedLabel(tmpConversationList.toVector().toStdVector());
    for (quint32 i = 0; i < friendsListMainWin->count(); i++)
    {
        friendsListConversations->addItem(friendsListMainWin->item(i)->data(0).toString());
        friendsListConversations->item(i)->setCheckState(Qt::CheckState::Unchecked);
        for (auto it : this->_conversationList)
        {
            if (it == friendsListConversations->item(i)->data(0).toString().toStdString())
                friendsListConversations->item(i)->setCheckState(Qt::CheckState::Checked);
        }
    }
    return (babel::Status(0, "UIManager 'updateFriendsListConversations()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshSelectedContact(std::string const& selectedContact, bool const isAConversation)
{
    QLabel              *selectedContactInformations = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getSelectedContactInformations();
    QLabel              *selectedContactChat = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get())->getSelectedContactChat();

    if (!selectedContactInformations || !selectedContactChat)
        return (babel::Status(1, "UIManager 'refreshSelectedContact()': A widget was null"));
    if (!isAConversation)
    {
        if (selectedContact != "")
        {
            selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\"font-weight:500;\">" +
                                                selectedContact +
                                                "</span></p><p style=\"margin: 2px\"><span style=\" font-style:italic; color:#56b921;\">Online</span></p></body></html>"));
            selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#4d4d4d;\">Chat empty :(</span></p></body></html>");
        }
        else
        {
            selectedContactInformations->setText("<html><head/><body><p><span style=\"font-style:italic;color:#4d4d4d ;\">No contact selected</span></p></body></html>");
            selectedContactChat->setText("<html><head/><body><p><span style=\"font-style:italic; color:#4d4d4d ;\">Select someone on the left to chat with someone!</span></p></body></html>");
        }
    }
    else
    {
        selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\" font-weight:496;\">" +
                                             selectedContact + "</span></p><p style=\"margin:2px\"><span style=\" \
                                             font-style:italic; color:#4d4d4d ;\">In conversation</span></p></body></html>"));
        selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#4d4d4d;\">Chat empty :(</span></p></body></html>");
    }
    return (babel::Status(0, "UIManager 'refreshSelectedContact()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromSignupToLoginDiag(std::string const& nickname)
{
    QLineEdit   *nicknameField = dynamic_cast<LoginDiag *>(this->_windowList["LoginDiag"].get())->getNicknameField();

    if (!nicknameField)
        return (babel::Status(1, "UIManager 'saveNicknameFromSignupToLoginDiag()': The NicknameField widget was null"));
    nicknameField->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromSignupToLoginDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::showErrorDialog(std::string const& dataText)
{
    CustomNotificationDiag *customNotificationDiag = dynamic_cast<CustomNotificationDiag *>(this->_windowList["CustomNotificationDiag"].get());

    if (!customNotificationDiag)
        return (babel::Status(1, "UIManager 'showErrorDialog()': The CustomNotification dialog was null"));
    customNotificationDiag->setDataText(QString::fromStdString(dataText));
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

void                                                                babel::UIManager::setConversationList(std::list<std::string> const& vStr)
{
    this->_conversationList = QList<std::string>::fromStdList(vStr);
}

void                                                                babel::UIManager::appendToConversationList(std::string const& nickname)
{
    this->_conversationList.append(nickname);
}

void                                                                babel::UIManager::removeToConversationlist(std::string const& nickname)
{
    this->_conversationList.removeAll(nickname);
}

void                                                                babel::UIManager::clearConversationList()
{
    this->_conversationList.clear();
}

babel::BabelClientManager                                           &babel::UIManager::getRoot()
{
    return (this->_root);
}

babel::BabelClientManager const                                     &babel::UIManager::getRoot() const
{
    return (this->_root);
}
