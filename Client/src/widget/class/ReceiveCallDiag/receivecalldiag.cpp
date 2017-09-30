#include "receivecalldiag.h"
#include "ui_receivecalldiag.h"

ReceiveCallDiag::ReceiveCallDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(std::make_shared<Ui::ReceiveCallDiag>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->DeclineButton, SIGNAL(clicked()), this, SLOT(DecliningCall()));
    QObject::connect(this->_ui->AcceptButton, SIGNAL(clicked()), this, SLOT(AcceptingCall()));
}

ReceiveCallDiag::~ReceiveCallDiag()
{

}

void            ReceiveCallDiag::setNameCallingText(std::string const& dataText)
{
    this->_ui->NameCallingText->setText(QString::fromStdString(dataText));
}

QPushButton     *ReceiveCallDiag::getDeclineButton()
{
    return (this->_ui->DeclineButton);
}

QPushButton     *ReceiveCallDiag::getAcceptButton()
{
    return (this->_ui->AcceptButton);
}

QLabel          *ReceiveCallDiag::getNameCallingText()
{
    return (this->_ui->NameCallingText);
}

void            ReceiveCallDiag::DecliningCall()
{
    this->_uiManager.decliningCall();
}

void            ReceiveCallDiag::AcceptingCall()
{
    this->_uiManager.acceptingCall();
}
