#include "logindiag.h"
#include "ui_logindiag.h"

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
    // Here are temporary connection
    if (this->_ui->NicknameField->text() == "Cauvin" && this->_ui->PasswordField->text() == "1235")
    {
        this->_uiManager.setNickname(this->_ui->NicknameField->text().toStdString());
        emit ConnectionAllowed();
    }
    else
        emit ConnectionDenied();
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
