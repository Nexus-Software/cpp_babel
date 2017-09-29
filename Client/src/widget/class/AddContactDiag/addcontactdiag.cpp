#include "addcontactdiag.h"
#include "ui_addcontactdiag.h"
#include "BabelClientManager.hpp"

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
	std::array<char, 2048> ba = { 0 };
	char contactC[32] = { 0 };

	this->_ui->SearchNameField->text().toStdString().copy(contactC, 32);

	std::string contact(contactC);

	std::copy(contact.begin(), contact.end(), ba.begin());

	this->_uiManager.getRoot().getNetwork().writeServerTCP(4, 32, ba);
}

void AddContactDiag::CloseContactWindow()
{
    this->_uiManager.hideWindow("AddContactDiag");
    this->_ui->SearchNameField->setText("");
}
