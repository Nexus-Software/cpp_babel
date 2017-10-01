#include "UIManager.hpp"
#include "BabelClientManager.hpp"

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
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    // Asks the server to check if the user does really exists
    // v Temporary not adding duplicated names v
    if (!mainWindow)
        return (babel::Status(1, "UIManager 'addContactToFriendsList()': mainWindow was null"));

    QListWidget *friendsList = mainWindow->getFriendsList();

    if (!friendsList)
        return (babel::Status(1, "UIManager 'addContactToFriendsList()': friendsList was null"));
    if (friendsList->count() == 50)
        this->showDialog("AddContactDiag", "Friends limit reached", "The friends limit has been reached (50).", babel::UIManager::DialogType::WARNING);
    else if (contactName.length() &&
        !friendsList->findItems(QString::fromStdString(contactName), Qt::MatchExactly).count())
    friendsList->addItem(QString::fromStdString(contactName));
    return (babel::Status(0, "UIManager 'addContactToFriendsList()' worked without error"));
}

babel::Status const                                                 babel::UIManager::closeContactWindow()
{
    AddContactDiag       *addContactDiag = dynamic_cast<AddContactDiag *>(this->_windowList["AddContactDiag"].get());

    if (!addContactDiag)
        return (babel::Status(1, "UIManager 'closeContactWindow()': addContactDiag was null"));

    this->hideWindow("AddContactDiag");
    addContactDiag->getSearchNameField()->setText("");
    return (babel::Status(0, "UIManager 'closeContactWindow()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshCurrentlySelectedLabel(std::vector<std::string> const& listSelected)
{
    AddToConversationDiag       *addToConversationDiag = dynamic_cast<AddToConversationDiag *>(this->_windowList["AddToConversationDiag"].get());

    if (!addToConversationDiag)
        return (babel::Status(1, "UIManager 'refreshCurrentlySelectedLabel()': addToConversationDiag was null"));

    QLabel                      *currentlySelectedLabel = addToConversationDiag->getCurrentlySelectedLabel();

    if (!currentlySelectedLabel)
        return (babel::Status(1, "UIManager 'refreshCurrentlySelectedLabel()': currentlySelectedLabel was null"));
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
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'refreshNewDataConversation()': mainWindow was null"));

    QListWidget *friendsList = mainWindow->getFriendsList();
    QPushButton *messageSendButton = mainWindow->getMessageSendButton();
    QLineEdit   *messageSendField = mainWindow->getMessageSendField();
    QPushButton *callButton = mainWindow->getCallButton();

    if (!friendsList || !messageSendButton || !messageSendField || !callButton)
        return (babel::Status(1, "UIManager 'refreshNewDataConversation()': A widget was null"));
    this->_conversationList = QList<std::string>::fromVector(QVector<std::string>::fromStdVector(newConversationList));
    for (int i = 0; i < friendsList->count(); i++)
    {
        if (this->_conversationList.length() != 1)
        {
            friendsList->item(i)->setSelected(false);
            if (this->_conversationList.isEmpty())
                this->refreshSelectedContact("", babel::UIManager::ContactInfoType::NO_CONTACT_SELECTED);
            else
                this->refreshSelectedContact(utils::join(this->_conversationList.toVector().toStdVector(), ", "), babel::UIManager::ContactInfoType::IN_CONVERSATION);
        }
        else
        {
            for (auto it : this->_conversationList)
            {
                if (friendsList->item(i)->data(0).toString().toStdString() == it)
                {
                    friendsList->item(i)->setSelected(true);
                    this->refreshSelectedContact(friendsList->item(i)->data(0).toString().toStdString(), babel::UIManager::ContactInfoType::ONLINE);
                }
                else
                    friendsList->item(i)->setSelected(false);
            }
        }
    }
    if (this->_conversationList.length() >= 1)
        callButton->setEnabled(true);
    else
        callButton->setEnabled(false);
    return (babel::Status(0, "UIManager 'refreshNewDataConversation()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromLoginToSignupDiag(std::string const& nickname)
{
    SignupDiag *signupDiag = dynamic_cast<SignupDiag *>(this->_windowList["SignupDiag"].get());

    if (!signupDiag)
        return (babel::Status(1, "UIManager 'saveNicknameFromLoginToSignupDiag()': signupDiag was null"));

    QLineEdit *nicknameField = signupDiag->getNicknameField();

    if (!nicknameField)
        return (babel::Status(1, "UIManager 'saveNicknameFromLoginToSignupDiag()': The NicknameField widget was null"));
    nicknameField->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromLoginToSignupDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::updateFriendsListFromContactManager()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'updateFriendsListFromContactManager()': mainWindow was null"));

    std::vector<babel::Contact> &contactList = this->_root.getContact().getContactList();
    QListWidget                 *friendsList = mainWindow->getFriendsList();

    if (!friendsList)
        return (babel::Status(1, "UIManager 'updateFriendsListFromContactManager()': friendsList was null"));
    friendsList->clear();
    for (auto it : contactList)
        friendsList->addItem(QString::fromStdString(it.getLogin()));

    return (babel::Status(0, "UIManager 'updateFriendsListFromContactManager()' worked without error"));
}

babel::Status const                                                 babel::UIManager::refreshGeneralInformations()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'refreshGeneralInformations()': mainWindow was null"));

    QLabel *generalInformations = mainWindow->getGeneralInformations();

    if (!generalInformations)
        return (babel::Status(1, "UIManager 'refreshGeneralInformations()': The GeneralInformations widget was null"));
    generalInformations->setText("<html><head/><body><p><span style=\" font-size:10pt;\">Welcome\
                                  </span><span style=\" font-size:10pt; font-weight:600;\">" + QString::fromStdString(this->_root.getContact().getUser().getLogin()) + "</span><span style=\"\
                                  font-size:10pt;\"> !</span></p><p><span style=\" font-size:10pt;\">There are </span><span style=\"\
                                  font-size:10pt; font-weight:600;\">" + QString::number(this->_friendsOnline) + "</span><span style=\" font-size:10pt;\">\
                                  friends connected.</span></p></body></html>");
    return (babel::Status(0, "UIManager 'changeNicknameGeneralInformations()' worked without error"));
}

babel::Status const                                                 babel::UIManager::updateFriendsListConversations()
{
    AddToConversationDiag       *addToConversationDiag = dynamic_cast<AddToConversationDiag *>(this->_windowList["AddToConversationDiag"].get());
    MainWindow                  *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!addToConversationDiag)
        return (babel::Status(1, "UIManager 'updateFriendsListConversations()': addToConversationDiag was null"));
    else if (!mainWindow)
        return (babel::Status(1, "UIManager 'updateFriendsListConversations()': mainWindow was null"));

    QListWidget                 *friendsListConversations = addToConversationDiag->getFriendsList();
    QListWidget                 *friendsListMainWin = mainWindow->getFriendsList();
    QLabel                      *currentlySelectedLabel = addToConversationDiag->getCurrentlySelectedLabel();
    QList<QListWidgetItem *>    selectedFriend;

    if (!friendsListConversations || !friendsListMainWin || !currentlySelectedLabel)
        return (babel::Status(1, "UIManager 'updateFriendsListConversations()': A widget was null"));
    selectedFriend = friendsListMainWin->selectedItems();

    QList<std::string> &tmpConversationList = addToConversationDiag->getTmpConversationList();

    while (friendsListConversations->count())
        delete friendsListConversations->takeItem(0);
    tmpConversationList.clear();
    for (auto it : this->_conversationList)
        tmpConversationList.append(it);
    this->refreshCurrentlySelectedLabel(tmpConversationList.toVector().toStdVector());
    for (int i = 0; i < friendsListMainWin->count(); i++)
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

babel::Status const                                                 babel::UIManager::refreshSelectedContact(std::string const& selectedContact, babel::UIManager::ContactInfoType const type)
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'refreshSelectedContact()': mainWindow was null"));

    QLabel              *selectedContactInformations = mainWindow->getSelectedContactInformations();
    QLabel              *selectedContactChat = mainWindow->getSelectedContactChat();

    if (!selectedContactInformations || !selectedContactChat)
        return (babel::Status(1, "UIManager 'refreshSelectedContact()': A widget was null"));

    switch (type)
    {
        case (babel::UIManager::ContactInfoType::ONLINE):
            selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\"font-weight:500;\">" +
                                                selectedContact +
                                                "</span></p><p style=\"margin: 2px\"><span style=\" font-style:italic; color:#56b921;\">Online</span></p></body></html>"));
            selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#4d4d4d;\">Chat empty :(</span></p></body></html>");
        break;
    case (babel::UIManager::ContactInfoType::CALLING_WAIT):
        selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\"font-weight:500;\">" +
                                                                    selectedContact + "</span></p><p style=\"margin:2px\"><span style=\" font-style:italic; color:#ffaa00;\">\
                                                                    Waiting..</span></p></body></html>"));
        selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#4d4d4d;\">Chat empty :(</span></p></body></html>");
        break;
    case (babel::UIManager::ContactInfoType::IN_CONVERSATION):
        selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\" font-weight:496;\">" +
                                             selectedContact + "</span></p><p style=\"margin:2px\"><span style=\" \
                                             font-style:italic; color:#4d4d4d ;\">Conversation</span></p></body></html>"));
        selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#4d4d4d;\">Chat empty :(</span></p></body></html>");
        break;
    case (babel::UIManager::ContactInfoType::IN_CALL):
        selectedContactInformations->setText(QString::fromStdString("<html><head/><body><p style=\"margin:2px\"><span style=\"font-weight:500;\">" +
                                                                    selectedContact + "</span></p><p style=\"margin:2px\"><span style=\" font-style:italic; color:#56b921;\">\
                                                                    In call</span></p></body></html>"));
        selectedContactChat->setText("<html><head/><body><p><span style=\" font-style:italic; color:#56b921;\">Chat empty :(</span></p></body></html>");
        break;
    case (babel::UIManager::ContactInfoType::NO_CONTACT_SELECTED):
        selectedContactInformations->setText("<html><head/><body><p><span style=\"font-style:italic;color:#4d4d4d ;\">No contact selected</span></p></body></html>");
        selectedContactChat->setText("<html><head/><body><p><span style=\"font-style:italic; color:#4d4d4d ;\">Select someone on the left to chat with someone!</span></p></body></html>");
        break;
    }
    return (babel::Status(0, "UIManager 'refreshSelectedContact()' worked without error"));
}

babel::Status const                                                 babel::UIManager::startCall()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'startCall()': mainWindow was null"));

    mainWindow->getCallButton()->setEnabled(false);
    mainWindow->getAddToConversationButton()->setEnabled(false);
    mainWindow->getHangupButton()->setEnabled(true);
    this->refreshSelectedContact(utils::join(this->_conversationList.toVector().toStdVector(), ", "), babel::UIManager::ContactInfoType::CALLING_WAIT);

    std::array<char, 2048>          ba = { 0 };
    std::uint32_t                   idConv = 0;
    std::uint32_t                   listeningPort = 0;
    QTcpServer                      tcpSocket;

    tcpSocket.listen(QHostAddress::LocalHost);
    listeningPort = tcpSocket.serverPort();
    tcpSocket.close();
	std::cout << "Client " << this->_root.getContact().getUser().getLogin() << " is listening on port " << listeningPort << std::endl;
	t_clientCallAcceptCall t;
	t.idconv = idConv;
	t.port = listeningPort;

	std::copy_n(reinterpret_cast<char *>(&t), sizeof(t), ba.data());

    this->getRoot().getCall().setOwner(true);
    this->getRoot().getNetwork().writeServerTCP(9, 64, ba);

    return (babel::Status(0, "UIManager 'startCall()' worked without error"));
}

babel::Status const                                                 babel::UIManager::hangupCall()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'hangupCall()': mainWindow was null"));

    QListWidget *friendsList = mainWindow->getFriendsList();

    if (!friendsList)
        return (babel::Status(1, "UIManager 'hangupCall()': friendsList was null"));
    mainWindow->getHangupButton()->setEnabled(false);
    mainWindow->getCallButton()->setEnabled(true);
    mainWindow->getAddToConversationButton()->setEnabled(true);
    if (this->_conversationList.count() != 1)
    {
        this->_conversationList.clear();
        for (int i = 0; i < friendsList->count(); i++)
            friendsList->item(i)->setSelected(false);
        this->refreshSelectedContact("", babel::UIManager::ContactInfoType::NO_CONTACT_SELECTED);
        mainWindow->getCallButton()->setEnabled(false);
        mainWindow->getAddToConversationButton()->setEnabled(true);
    }
    else
        this->refreshSelectedContact(this->_conversationList[0], babel::UIManager::ContactInfoType::ONLINE);

    return (babel::Status(0, "UIManager 'hangupCall()' worked without error"));
}

babel::Status const                                                 babel::UIManager::selectedFriendClicked(std::string const& contactName)
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'selectedFriendClicked()': mainWindow was null"));

    this->clearConversationList();
    this->appendToConversationList(contactName);
    this->refreshSelectedContact(contactName, babel::UIManager::ContactInfoType::ONLINE);
    mainWindow->getCallButton()->setEnabled(true);
    return (babel::Status(0, "UIManager 'selectedFriendClicked()' worked without error"));
}

babel::Status const                                         babel::UIManager::removeFriend()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'removeFriend()': mainWindow was null"));

    for (int i = 0; i < mainWindow->getFriendsList()->selectedItems().size(); ++i) {
        QListWidgetItem *item = mainWindow->getFriendsList()->takeItem(mainWindow->getFriendsList()->currentRow());

        std::array<char, 2048>  ba = { 0 };
        std::string             nickname(item->data(0).toString().toStdString());

        std::copy(nickname.begin(), nickname.end(), ba.begin());

        this->getRoot().getNetwork().writeServerTCP(3, 32, ba);
        delete item;
    }
    return (babel::Status(0, "UIManager 'removeFriend()' worked without error"));
}

babel::Status const                                         babel::UIManager::decliningCall()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'removeFriend()': mainWindow was null"));

    QListWidget *friendsList = mainWindow->getFriendsList();

    if (!friendsList)
        return (babel::Status(1, "UIManager 'addContactToFriendsList()': friendsList was null"));

    mainWindow->getHangupButton()->setEnabled(false);
    mainWindow->getCallButton()->setEnabled(true);
    mainWindow->getAddToConversationButton()->setEnabled(true);
    std::cout << "---------------> length of conversationlist: " << this->_conversationList.count() << std::endl;
    if (this->_conversationList.length() == 1)
        this->refreshSelectedContact(this->_conversationList[0], babel::UIManager::ContactInfoType::ONLINE);
    else if (this->_conversationList.length() > 1)
    {
        this->_conversationList.clear();
        for (int i = 0; i < friendsList->count(); i++)
            friendsList->item(i)->setSelected(false);
        mainWindow->getCallButton()->setEnabled(false);
        this->refreshSelectedContact("", babel::UIManager::ContactInfoType::NO_CONTACT_SELECTED);
    }
    this->hideWindow("ReceiveCallDiag");
    return (babel::Status(0, "UIManager 'decliningCall()' worked without error"));
}

babel::Status const                                         babel::UIManager::acceptingCall()
{
    std::array<char, 2048>          ba = { 0 };
    std::uint32_t                   idConv = this->_root.getCall().getCurrentCall().getIdConv();
    std::uint32_t                   listeningPort = 0;
    QTcpServer                      tcpSocket;

    tcpSocket.listen(QHostAddress::LocalHost, 0);
    listeningPort = tcpSocket.serverPort();
    tcpSocket.close();
	this->_root.getNetwork().getNetworkUdp()->serverBind(listeningPort);
	std::cout << "Client " << this->_root.getContact().getUser().getLogin() << " is listening on port " << listeningPort << std::endl;
	t_clientCallAcceptCall t;
	t.idconv = idConv;
	t.port = listeningPort;

	std::copy_n(reinterpret_cast<char *>(&t), sizeof(t), ba.data());
  
    this->getRoot().getCall().setOwner(false);
    this->getRoot().getNetwork().writeServerTCP(9, 64, ba);

    return (babel::Status(0, "UIManager 'acceptingCall()' worked without error"));
}

babel::Status const                                                 babel::UIManager::updateNameCallingText(std::string const& nickname)
{
    ReceiveCallDiag *receiveCallDiag = dynamic_cast<ReceiveCallDiag *>(this->_windowList["ReceiveCallDiag"].get());

    if (!receiveCallDiag)
        return (babel::Status(1, "UIManager 'updateNameCallingText()': receiveCallDiag was null"));

    receiveCallDiag->setNameCallingText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:500;\">" +
                                        nickname +
                                        "</span><span style=\" font-size:12pt;\"> is calling you...</span></p></body></html>");

    return (babel::Status(0, "UIManager 'updateNameCallingText()' worked without error"));
}

babel::Status const                                                 babel::UIManager::updateNameCallingText(std::string const& nicknameHost, std::vector<std::string> const& otherPeople)
{
    ReceiveCallDiag *receiveCallDiag = dynamic_cast<ReceiveCallDiag *>(this->_windowList["ReceiveCallDiag"].get());

    if (!receiveCallDiag)
        return (babel::Status(1, "UIManager 'updateNameCallingText()': receiveCallDiag was null"));

    receiveCallDiag->setNameCallingText("<html><head/><body><p><span style=\" font-size:12pt; font-weight:500;\">" + nicknameHost +
                                        "</span><span style=\" font-size:12pt;\"> has invited you, along with </span><span style=\" font-size:12pt; font-weight:500;\">" +
                                        utils::join(otherPeople, ", ") +
                                        "</span><span style=\" font-size:12pt;\">...</span></p></body></html>");

    return (babel::Status(0, "UIManager 'updateNameCallingText()' worked without error"));
}

babel::Status const                                                 babel::UIManager::saveNicknameFromSignupToLoginDiag(std::string const& nickname)
{
    LoginDiag *loginDiag = dynamic_cast<LoginDiag *>(this->_windowList["LoginDiag"].get());

    if (!loginDiag)
        return (babel::Status(1, "UIManager 'saveNicknameFromSignupToLoginDiag()': loginDiag was null"));

    QLineEdit   *nicknameField = loginDiag->getNicknameField();

    if (!nicknameField)
        return (babel::Status(1, "UIManager 'saveNicknameFromSignupToLoginDiag()': The NicknameField widget was null"));
    nicknameField->setText(QString::fromStdString(nickname));
    return (babel::Status(0, "UIManager 'saveNicknameFromSignupToLoginDiag()' worked without error"));
}

babel::Status const                                                 babel::UIManager::showDialog(std::string const& widget, std::string const& titleText, std::string const& dataText, babel::UIManager::DialogType const type)
{
    QWidget *w = this->_windowList[widget].get();

    if (!w)
        return (babel::Status(1, "UIManager 'showDialog()': The widget was null or not found"));
    switch (type)
    {
        case (babel::UIManager::DialogType::WARNING):
            QMessageBox::warning(w, QString::fromStdString(titleText), QString::fromStdString(dataText));
            break;
        case (babel::UIManager::DialogType::CRITICAL):
            QMessageBox::critical(w, QString::fromStdString(titleText), QString::fromStdString(dataText));
            break;
        case (babel::UIManager::DialogType::INFORMATION):
            QMessageBox::information(w, QString::fromStdString(titleText), QString::fromStdString(dataText));
            break;
        case (babel::UIManager::DialogType::QUESTION):
            QMessageBox::question(w, QString::fromStdString(titleText), QString::fromStdString(dataText));
            break;
    }
    return (babel::Status(0, "UIManager 'showDialog()' worked without error"));
}

babel::Status const													babel::UIManager::inviteContactInConversation()
{
    for (auto it : this->_conversationList)
        this->inviteToCall(it);
	return (babel::Status(0, "UIManager 'inviteContactInConversation()' worked without error"));
}

babel::Status const                                                 babel::UIManager::inviteToCall(std::string const& nickname)
{
	std::array<char, 2048>  ba = { 0 };
	babel::t_clientCallInvite	t = {0};

	t.idCall = this->_root.getCall().getCurrentcall().getIdConv();

	std::cout << "--------- INVITE IDCONV: " << t.idCall << std::endl;

	nickname.copy(t.loginInvite, 32);

	std::copy_n(reinterpret_cast<const char *>(&t), sizeof(t), ba.begin());

    this->getRoot().getNetwork().writeServerTCP(7, 64, ba);

    return (babel::Status(0, "UIManager 'inviteToCall()' worked without error"));
}


babel::Status const                                                 babel::UIManager::refreshStatusWhenReceivingCall()
{
    MainWindow *mainWindow = dynamic_cast<MainWindow *>(this->_windowList["MainWindow"].get());

    if (!mainWindow)
        return (babel::Status(1, "UIManager 'refreshStatusWhenReceivingCall()': mainWindow was null"));


    QListWidget *friendsList = mainWindow->getFriendsList();

    if (!friendsList)
        return (babel::Status(1, "UIManager 'refreshStatusWhenReceivingCall()': friendsList was null"));

    mainWindow->getAddToConversationButton()->setEnabled(false);
    mainWindow->getCallButton()->setEnabled(false);
    if (this->_conversationList.length() == 1)
    {
        for (int i = 0; i < friendsList->count(); i++)
        {
            for (auto it : this->_conversationList)
                friendsList->item(i)->setSelected(friendsList->item(i)->data(0).toString().toStdString() == it);
        }
    }
    else if (this->_conversationList.length() > 1)
    {
        for (int i = 0; i < friendsList->count(); i++)
            friendsList->item(i)->setSelected(false);
    }
    this->refreshSelectedContact(utils::join(this->_conversationList.toVector().toStdVector(), ", "), babel::UIManager::ContactInfoType::CALLING_WAIT);
    return (babel::Status(0, "UIManager 'refreshStatusWhenReceivingCall()' worked without error"));
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
