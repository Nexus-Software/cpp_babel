#include "logindiag.h"
#include "ui_logindiag.h"
#include "BabelClientManager.hpp"

LoginDiag::LoginDiag(QWidget *parent, babel::UIManager &uiManager) :
    QDialog(parent),
    _ui(std::make_shared<Ui::LoginDiag>()),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);
    this->setFixedSize(this->size());

    QObject::connect(this->_ui->SignupButton, SIGNAL(clicked()), this, SLOT(SwitchToSignupWindow()));
    QObject::connect(this->_ui->ConnectButton, SIGNAL(clicked()), this, SLOT(WaitingForResponse()));
    QObject::connect(this, SIGNAL(ConnectionAllowed()), this, SLOT(SwitchToMainWindow()));
    QObject::connect(this, SIGNAL(ConnectionDenied()), this, SLOT(ShowErrorDialog()));
}


LoginDiag::~LoginDiag()
{

}

void                LoginDiag::enableAllObjects(bool const areDisabled)
{
    this->_ui->NicknameField->setEnabled(areDisabled);
    this->_ui->PasswordField->setEnabled(areDisabled);
    this->_ui->SignupButton->setEnabled(areDisabled);
    this->_ui->ConnectButton->setEnabled(areDisabled);
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
    this->_uiManager.hideWindow("LoginDiag");
    this->_uiManager.saveNicknameFromLoginToSignupDiag(this->_ui->NicknameField->text().toStdString());
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_uiManager.showWindow("SignupDiag");
}

void LoginDiag::WaitingForResponse() {
    this->enableAllObjects(false);
    // Request to the server if credentials are correct
    this->_uiManager.setNickname(this->_ui->NicknameField->text().toStdString());

	std::array<char, 2048> ba = { 0 };
	char usernameC[32] = { 0 };
	char passwordC[32] = { 0 };

	this->_ui->NicknameField->text().toStdString().copy(usernameC, 32);
	this->_ui->PasswordField->text().toStdString().copy(passwordC, 32);

	std::string username(usernameC);
	std::string password(passwordC);

	std::copy(username.begin(), username.end(), ba.begin());
	std::copy(password.begin(), password.end(), ba.begin() + 32);

	this->_uiManager.getRoot().getNetwork().writeServerTCP(2, 64, ba);
	this->_uiManager.setNickname(this->_ui->NicknameField->text().toStdString());
   
    this->enableAllObjects(true);
}

void LoginDiag::SwitchToMainWindow() {
    this->_uiManager.hideWindow("LoginDiag");
    this->_ui->NicknameField->setText("");
    this->_ui->PasswordField->setText("");
    this->_uiManager.refreshGeneralInformations();
    this->_uiManager.showWindow("MainWindow");
}

void LoginDiag::ShowErrorDialog() {
    QMessageBox::warning(this, "Login", "Wrong nickname or the password entered was incorrect.");
}
