#include "receivecalldiag.h"
#include "ui_receivecalldiag.h"

ReceiveCallDiag::ReceiveCallDiag(QWidget *parent, babel::UIManager *uiManager) :
    QDialog(parent),
    _ui(new Ui::ReceiveCallDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());
}

ReceiveCallDiag::~ReceiveCallDiag()
{
    delete (this->_ui);
}
