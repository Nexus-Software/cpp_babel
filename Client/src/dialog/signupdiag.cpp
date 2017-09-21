#include "./include/QTHeaders/signupdiag.h"
#include "ui_signupdiag.h"

SignupDiag::SignupDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignupDiag)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

SignupDiag::~SignupDiag()
{
    delete ui;
}
