#include "addcontactdiag.h"
#include "ui_addcontactdiag.h"

AddContactDiag::AddContactDiag(QWidget *parent, babel::UIManager *uiManager) :
    QDialog(parent),
    _ui(new Ui::AddContactDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());
}

AddContactDiag::~AddContactDiag()
{
    delete (this->_ui);
}
