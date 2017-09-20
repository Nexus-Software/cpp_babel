#include "dialogreceivecall.h"
#include "ui_dialogreceivecall.h"

DialogReceiveCall::DialogReceiveCall(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogReceiveCall)
{
    ui->setupUi(this);
}

DialogReceiveCall::~DialogReceiveCall()
{
    delete ui;
}
