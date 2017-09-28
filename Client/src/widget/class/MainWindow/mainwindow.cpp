#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, babel::UIManager &uiManager) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);

    QList<int> sizes;
    sizes << 30 << 350;
    this->_ui->WindowSplitter->setSizes(sizes);

    QObject::connect(this->_ui->FilterFriendField, SIGNAL(textChanged(QString const&)), this, SLOT(FilterFriendsList(QString const&)));
    QObject::connect(this->_ui->ActionDisconnect, SIGNAL(triggered()), this, SLOT(RedirectToLoginDiag()));
    QObject::connect(this->_ui->ActionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(this->_ui->FriendsList, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(SelectedFriendClicked(QListWidgetItem *)));
    QObject::connect(this->_ui->AddContactButton, SIGNAL(clicked()), this, SLOT(OpenAddContactDiag()));
    QObject::connect(this->_ui->AddToConversationButton, SIGNAL(clicked()), this, SLOT(OpenAddToConversationDiag()));
}

MainWindow::~MainWindow()
{
    delete (this->_ui);
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

void                    MainWindow::RedirectToLoginDiag()
{
    QList<QListWidgetItem *> selectedItems = this->_ui->FriendsList->selectedItems();

    this->_uiManager.hideWindow("MainWindow");
    while (this->_ui->FriendsList->count())
        this->_ui->FriendsList->takeItem(0);
    this->_ui->SelectedContactInformations->setText("<html><head/><body><p><span style=\"font-style:italic;color:#4d4d4d ;\">No contact selected</span></p></body></html>");
    this->_ui->SelectedContactChat->setText("<html><head/><body><p><span style=\"font-style:italic; color:#4d4d4d ;\">Select someone on the left to chat with someone!</span></p></body></html>");
    this->_ui->MessageSendField->setEnabled(false);
    this->_ui->MessageSendButton->setEnabled(false);
    this->_ui->FilterFriendField->setText("");
    this->_uiManager.showWindow("LoginDiag");
}

void                    MainWindow::SelectedFriendClicked(QListWidgetItem *selectedContact)
{
    this->_uiManager.clearConversationList();
    this->_uiManager.appendToConversationList(selectedContact->data(0).toString().toStdString());
    this->_uiManager.refreshSelectedContact(selectedContact->data(0).toString().toStdString(), false);
    this->_ui->MessageSendButton->setEnabled(true);
    this->_ui->MessageSendField->setEnabled(true);
    this->_ui->CallButton->setEnabled(true);
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
