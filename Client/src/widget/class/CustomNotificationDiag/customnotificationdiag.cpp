#include "customnotificationdiag.h"
#include "ui_customnotificationdiag.h"

CustomNotificationDiag::CustomNotificationDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(std::make_shared<Ui::CustomNotificationDiag>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());
}

CustomNotificationDiag::~CustomNotificationDiag()
{

}

void    CustomNotificationDiag::setDataText(QString const& dataText)
{
    this->_ui->DataText->setText(dataText);
}

QString const CustomNotificationDiag::getDataText() const
{
    return (this->_ui->DataText->text());
}
