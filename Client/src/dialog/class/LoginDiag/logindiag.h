#ifndef LOGINDIAG_H
#define LOGINDIAG_H

#include <QDialog>
#include <QLineEdit>
#include "UIManager.hpp"

namespace babel {
    class UIManager;
}

namespace Ui {
class LoginDiag;
}

class LoginDiag : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDiag(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~LoginDiag();

    QLineEdit           *getNicknameField();
    QLineEdit           *getPasswordField();
    QPushButton         *getSignupButton();
    QPushButton         *getConnectButton();

public slots:
    void SwitchToSignupWindow();

private:
    Ui::LoginDiag *_ui;
    babel::UIManager *_uiManager;
};

#endif // LOGINDIAG_H
