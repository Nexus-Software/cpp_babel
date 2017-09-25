#include "signupdiag.h"
#include "ui_signupdiag.h"

SignupDiag::SignupDiag(QWidget *parent, babel::UIManager *uiManager) :
    QDialog(parent),
    _ui(new Ui::SignupDiag),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->LoginButton, SIGNAL(clicked()), this, SLOT(SwitchToLoginWindow()));
}

QLineEdit           *SignupDiag::getNicknameField()
{
    return (this->_ui->NicknameField);
}

QLineEdit           *SignupDiag::getPasswordField()
{
    return (this->_ui->PasswordField);
}

QLineEdit           *SignupDiag::getConfirmField()
{
    return (this->_ui->ConfirmField);
}

QPushButton         *SignupDiag::getLoginButton()
{
    return (this->_ui->LoginButton);
}

QPushButton         *SignupDiag::getRegisterButton()
{
    return (this->_ui->RegisterButton);
}

void SignupDiag::SwitchToLoginWindow() {
    this->_uiManager->hideWindow("SignupDiag");
    dynamic_cast<LoginDiag *>(this->_uiManager->getWindowList()["LoginDiag"].get())->getNicknameField()->setText(this->_ui->NicknameField->text());
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_uiManager->showWindow("LoginDiag");
}

SignupDiag::~SignupDiag()
{
    delete (this->_ui);
}
