#include "./include/QTHeaders/logindiag.h"
#include "ui_logindiag.h"

LoginDiag::LoginDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDiag)
{
    ui->setupUi(this);
}

LoginDiag::~LoginDiag()
{
    delete ui;
}
