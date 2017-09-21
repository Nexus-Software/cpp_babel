#include "./include/QTHeaders/customnotificationdiag.h"
#include "ui_customnotificationdiag.h"

CustomNotificationDiag::CustomNotificationDiag(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomNotificationDiag)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

CustomNotificationDiag::~CustomNotificationDiag()
{
    delete ui;
}
