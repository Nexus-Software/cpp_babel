#ifndef SIGNUPDIAG_H
#define SIGNUPDIAG_H

#include <QDialog>
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
    explicit SignupDiag(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~SignupDiag();

    QLineEdit           *getNicknameField();
    QLineEdit           *getPasswordField();
    QLineEdit           *getConfirmField();
    QPushButton         *getLoginButton();
    QPushButton         *getRegisterButton();

public slots:
    void SwitchToLoginWindow();

private:
    Ui::SignupDiag *_ui;
    babel::UIManager *_uiManager;
};

#endif // SIGNUPDIAG_H
