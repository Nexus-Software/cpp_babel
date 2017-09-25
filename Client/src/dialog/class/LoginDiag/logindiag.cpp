#include "logindiag.h"
#include "ui_logindiag.h"

LoginDiag::LoginDiag(QWidget *parent, babel::UIManager *uiManager) :
    QDialog(parent),
    _ui(new Ui::LoginDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->SignupButton, SIGNAL(clicked()), this, SLOT(SwitchToSignupWindow()));
}

QLineEdit           *LoginDiag::getNicknameField()
{
    return (this->_ui->NicknameField);
}

QLineEdit           *LoginDiag::getPasswordField()
{
    return (this->_ui->PasswordField);
}

QPushButton         *LoginDiag::getSignupButton()
{
    return (this->_ui->SignupButton);
}

QPushButton         *LoginDiag::getConnectButton()
{
    return (this->_ui->ConnectButton);
}

void LoginDiag::SwitchToSignupWindow() {
    this->_uiManager->hideWindow("LoginDiag");
    dynamic_cast<SignupDiag *>(this->_uiManager->getWindowList()["SignupDiag"].get())->getNicknameField()->setText(this->_ui->NicknameField->text());
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_uiManager->showWindow("SignupDiag");
}

LoginDiag::~LoginDiag()
{
    delete (this->_ui);
}
