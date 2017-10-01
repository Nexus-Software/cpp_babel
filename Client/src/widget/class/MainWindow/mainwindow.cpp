#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, babel::UIManager &uiManager) :
    QMainWindow(parent),
    _ui(std::make_shared<Ui::MainWindow>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);

    QList<int> sizes;
    sizes << 30 << 350;
    this->_ui->WindowSplitter->setSizes(sizes);

    QObject::connect(this->_ui->FilterFriendField, SIGNAL(textChanged(QString const&)), this, SLOT(FilterFriendsList(QString const&)));
    QObject::connect(this->_ui->ActionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(this->_ui->FriendsList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(SelectedFriendClicked(QListWidgetItem *)));
    QObject::connect(this->_ui->FriendsList, SIGNAL(customContextMenuRequested(QPoint const&)), this, SLOT(ShowContextMenu(QPoint const&)));
    QObject::connect(this->_ui->AddContactButton, SIGNAL(clicked()), this, SLOT(OpenAddContactDiag()));
    QObject::connect(this->_ui->AddToConversationButton, SIGNAL(clicked()), this, SLOT(OpenAddToConversationDiag()));
    QObject::connect(this->_ui->CallButton, SIGNAL(clicked()), this, SLOT(StartingCall()));
    QObject::connect(this->_ui->HangupButton, SIGNAL(clicked()), this, SLOT(HangingUpCall()));
}

MainWindow::~MainWindow()
{

}

QListWidget             *MainWindow::getFriendsList()
{
    return (this->_ui->FriendsList);
}

QLabel                  *MainWindow::getGeneralInformations()
{
    return (this->_ui->GeneralInformations);
}

QLabel                  *MainWindow::getSelectedContactInformations()
{
    return (this->_ui->SelectedContactInformations);
}

QLabel                  *MainWindow::getSelectedContactChat()
{
    return (this->_ui->SelectedContactChat);
}

QPushButton             *MainWindow::getMessageSendButton()
{
    return (this->_ui->MessageSendButton);
}

QLineEdit               *MainWindow::getMessageSendField()
{
    return (this->_ui->MessageSendField);
}

QPushButton             *MainWindow::getCallButton()
{
    return (this->_ui->CallButton);
}

QPushButton             *MainWindow::getHangupButton()
{
    return (this->_ui->HangupButton);
}

QPushButton             *MainWindow::getAddToConversationButton()
{
    return (this->_ui->AddToConversationButton);
}

QLineEdit               *MainWindow::getFilterFriendField()
{
    return (this->_ui->FilterFriendField);
}

QPushButton             *MainWindow::getAddContactButton()
{
    return (this->_ui->AddContactButton);
}

void                    MainWindow::FilterFriendsList(QString const& filterText)
{
    QList<QListWidgetItem *> filteredList = this->_ui->FriendsList->findItems(filterText, Qt::MatchContains);

    if (!filterText.isEmpty())
    {
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
            this->_ui->FriendsList->item(i)->setHidden(true);
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
        {
            for (int j = 0; j < filteredList.count(); j++)
            {
                if (this->_ui->FriendsList->item(i)->data(0).toString().toStdString() == filteredList[j]->data(0).toString().toStdString())
                    this->_ui->FriendsList->item(i)->setHidden(false);
            }
        }
    }
    else
    {
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
            this->_ui->FriendsList->item(i)->setHidden(false);
    }
}

void                    MainWindow::SelectedFriendClicked(QListWidgetItem *selectedContact)
{
    this->_uiManager.selectedFriendClicked(selectedContact->data(0).toString().toStdString());
}

void                    MainWindow::ShowContextMenu(QPoint const& pos)
{
    QPoint  globalPos = this->_ui->FriendsList->mapToGlobal(pos);
    QMenu   menu;

    menu.addAction("Call", this, SLOT(ContextStartingCall()));
    menu.addAction("Remove",  this, SLOT(RemoveFriend()));

    if (!this->_uiManager.isSelectedContactOnline() && menu.actions().size() == 2)
        menu.actions()[0]->setEnabled(false);

    menu.exec(globalPos);
}

void                    MainWindow::OpenAddContactDiag()
{
    this->_uiManager.showWindow("AddContactDiag");
    this->_ui->FilterFriendField->setText("");
}

void                    MainWindow::OpenAddToConversationDiag()
{
    this->_uiManager.showWindow("AddToConversationDiag");
    this->_uiManager.updateFriendsListConversations();
}

void                    MainWindow::StartingCall()
{
    this->_uiManager.startCall();
}

void                    MainWindow::ContextStartingCall()
{
    this->_uiManager.contextStartingCall();
}

void                    MainWindow::HangingUpCall()
{
    this->_uiManager.hangupCall();
}

void                    MainWindow::RemoveFriend()
{
    this->_uiManager.removeFriend();
}
