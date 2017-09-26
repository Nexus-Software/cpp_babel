#include "addcontactdiag.h"
#include "ui_addcontactdiag.h"

AddContactDiag::AddContactDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(new Ui::AddContactDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->AddContactButton, SIGNAL(clicked()), this, SLOT(AddSelectedContact()));
    QObject::connect(this->_ui->CloseButton, SIGNAL(clicked()), this, SLOT(CloseContactWindow()));
}

AddContactDiag::~AddContactDiag()
{
    delete (this->_ui);
}

void AddContactDiag::AddSelectedContact()
{
    QListWidget *friendsList = dynamic_cast<MainWindow *>(this->_uiManager.getWindowList()["MainWindow"].get())->getFriendsList();

    // Asks the server to check if the user does really exists
    // v Temporary not adding duplicated names v
    if (friendsList && this->_ui->SearchNameField->text().length() &&
        !friendsList->findItems(this->_ui->SearchNameField->text(), Qt::MatchExactly).count())
        friendsList->addItem(this->_ui->SearchNameField->text());
}

void AddContactDiag::CloseContactWindow()
{
    this->_uiManager.hideWindow("AddContactDiag");
}
