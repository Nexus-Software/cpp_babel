#ifndef SIGNUPDIAG_H
#define SIGNUPDIAG_H

#include <QDialog>
#include <QMessageBox>
#include "UIManager.hpp"

namespace Ui {
    class SignupDiag;
}

namespace babel {
    class UIManager;
}

class SignupDiag : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDiag(QWidget *parent, babel::UIManager &uiManager);
    ~SignupDiag();

    void                enableAllObjects(bool const areDisabled);

    QLineEdit           *getNicknameField();
    QLineEdit           *getPasswordField();
    QLineEdit           *getConfirmField();
    QPushButton         *getLoginButton();
    QPushButton         *getRegisterButton();

public slots:
    void SwitchToLoginWindow();
    void WaitingForResponse();
    void SwitchToMainWindow();
    void ShowErrorDialog();

signals:
    void ConnectionDenied();

private:
    std::shared_ptr<Ui::SignupDiag> _ui;
    babel::UIManager                &_uiManager;
};

#endif // SIGNUPDIAG_H
