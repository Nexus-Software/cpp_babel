#include "./include/QTHeaders/receivecalldiag.h"
#include "ui_receivecalldiag.h"

ReceiveCallDiag::ReceiveCallDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveCallDiag)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

ReceiveCallDiag::~ReceiveCallDiag()
{
    delete ui;
}
