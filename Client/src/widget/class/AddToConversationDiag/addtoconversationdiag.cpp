#include "addtoconversationdiag.h"
#include "ui_addtoconversationdiag.h"

AddToConversationDiag::AddToConversationDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(new Ui::AddToConversationDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->CancelButton, SIGNAL(clicked()), this, SLOT(CancelActionAddToConversationWindow()));
    QObject::connect(this->_ui->ConfirmButton, SIGNAL(clicked()), this, SLOT(ConfirmActionAddToConversationWindow()));
    QObject::connect(this->_ui->FriendsList, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(RefreshFriendsInConversation(QListWidgetItem *)));
}

AddToConversationDiag::~AddToConversationDiag()
{
    delete this->_ui;
}

QListWidget                 *AddToConversationDiag::getFriendsList() const
{
    return (this->_ui->FriendsList);
}

QLabel                      *AddToConversationDiag::getCurrentlySelectedLabel() const
{
    return (this->_ui->CurrentlySelectedLabel);
}

QList<std::string>          &AddToConversationDiag::getTmpConversationList()
{
    return (this->_tmpConversationList);
}

void                        AddToConversationDiag::CancelActionAddToConversationWindow()
{
    this->_uiManager.hideWindow("AddToConversationDiag");
}

void                        AddToConversationDiag::ConfirmActionAddToConversationWindow()
{
    this->_uiManager.hideWindow("AddToConversationDiag");
    this->_uiManager.refreshNewDataConversation(this->_tmpConversationList.toVector().toStdVector());
}

void                        AddToConversationDiag::RefreshFriendsInConversation(QListWidgetItem *item)
{
    if (item->checkState())
        this->_tmpConversationList.append(item->data(0).toString().toStdString());
    else
        this->_tmpConversationList.removeAll(item->data(0).toString().toStdString());
    this->_uiManager.refreshCurrentlySelectedLabel(this->_tmpConversationList.toVector().toStdVector());
}
