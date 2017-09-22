#include "addcontactdiag.h"
#include "ui_addcontactdiag.h"

AddContactDiag::AddContactDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContactDiag)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

AddContactDiag::~AddContactDiag()
{
    delete ui;
}
