#include "signupdiag.h"
#include "ui_signupdiag.h"

SignupDiag::SignupDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(std::make_shared<Ui::SignupDiag>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->LoginButton, SIGNAL(clicked()), this, SLOT(SwitchToLoginWindow()));
    QObject::connect(this->_ui->RegisterButton, SIGNAL(clicked()), this, SLOT(WaitingForResponse()));
    QObject::connect(this, SIGNAL(ConnectionAllowed()), this, SLOT(SwitchToMainWindow()));
    QObject::connect(this, SIGNAL(ConnectionDenied()), this, SLOT(ShowErrorDialog()));
}

SignupDiag::~SignupDiag()
{

}

void                SignupDiag::enableAllObjects(bool const areDisabled)
{
    this->_ui->NicknameField->setEnabled(areDisabled);
    this->_ui->PasswordField->setEnabled(areDisabled);
    this->_ui->ConfirmField->setEnabled(areDisabled);
    this->_ui->LoginButton->setEnabled(areDisabled);
    this->_ui->RegisterButton->setEnabled(areDisabled);
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
    this->_uiManager.hideWindow("SignupDiag");
    this->_uiManager.saveNicknameFromSignupToLoginDiag(this->_ui->NicknameField->text().toStdString());
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_ui->ConfirmField->setText("");
    this->_uiManager.showWindow("LoginDiag");
}

void SignupDiag::WaitingForResponse() {
    this->enableAllObjects(false);
    // v This + if that nickname isn't not already registered v
    if (this->_ui->PasswordField->text() == this->_ui->ConfirmField->text())
    {
        this->_uiManager.setNickname(this->_ui->NicknameField->text().toStdString());
        emit ConnectionAllowed();
    }
    else
        emit ConnectionDenied();
    this->enableAllObjects(true);
}

void SignupDiag::SwitchToMainWindow() {
    this->_uiManager.hideWindow("SignupDiag");
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_ui->ConfirmField->setText("");
    this->_uiManager.refreshGeneralInformations();
    this->_uiManager.showWindow("MainWindow");
}

void SignupDiag::ShowErrorDialog() {
    QMessageBox::warning(this, "Signup", "The nickname you entered is already used or both passwords does not match.");
}
