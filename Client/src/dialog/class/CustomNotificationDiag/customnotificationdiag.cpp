#include "customnotificationdiag.h"
#include "ui_customnotificationdiag.h"

CustomNotificationDiag::CustomNotificationDiag(QWidget *parent, babel::UIManager *uiManager) :
    QDialog(parent),
    _ui(new Ui::CustomNotificationDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());
}

CustomNotificationDiag::~CustomNotificationDiag()
{
    delete (this->_ui);
}
