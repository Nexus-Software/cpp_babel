#include "logindiag.h"
#include "ui_logindiag.h"

LoginDiag::LoginDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDiag)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

LoginDiag::~LoginDiag()
{
    delete ui;
}
