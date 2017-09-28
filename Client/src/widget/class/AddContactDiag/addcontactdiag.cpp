#include "addcontactdiag.h"
#include "ui_addcontactdiag.h"

AddContactDiag::AddContactDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(std::make_shared<Ui::AddContactDiag>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->AddContactButton, SIGNAL(clicked()), this, SLOT(AddContact()));
    QObject::connect(this->_ui->CloseButton, SIGNAL(clicked()), this, SLOT(CloseContactWindow()));
}

AddContactDiag::~AddContactDiag()
{

}

void AddContactDiag::AddContact()
{
    this->_uiManager.addContactToFriendsList(this->_ui->SearchNameField->text().toStdString());
}

void AddContactDiag::CloseContactWindow()
{
    this->_uiManager.hideWindow("AddContactDiag");
    this->_ui->SearchNameField->setText("");
}
