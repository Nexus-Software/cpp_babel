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
    explicit LoginDiag(QWidget *parent, babel::UIManager &uiManager);
    ~LoginDiag();

    void                enableAllObjects(bool const areDisabled);

    QLineEdit           *getNicknameField();
    QLineEdit           *getPasswordField();
    QPushButton         *getSignupButton();
    QPushButton         *getConnectButton();

public slots:
    void SwitchToSignupWindow();
    void WaitingForResponse();
    void SwitchToMainWindow();
    void ShowErrorDialog();

signals:
    void ConnectionAllowed();
    void ConnectionDenied();

private:
    std::shared_ptr<Ui::LoginDiag>  _ui;
    babel::UIManager                &_uiManager;
};

#endif // LOGINDIAG_H
