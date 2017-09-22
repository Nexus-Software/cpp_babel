#include "signupdiag.h"
#include "ui_signupdiag.h"

SignupDiag::SignupDiag(QWidget *parent) :
    QDialog(parent),
    _ui(new Ui::SignupDiag)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());
}
SignupDiag::~SignupDiag()
{
    delete (this->_ui);
}
