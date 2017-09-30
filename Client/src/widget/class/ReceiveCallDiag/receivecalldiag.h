#ifndef RECEIVECALLDIAG_H
#define RECEIVECALLDIAG_H

#include <QDialog>
#include "UIManager.hpp"

namespace Ui {
class ReceiveCallDiag;
}

namespace babel {
    class UIManager;
}

class ReceiveCallDiag : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveCallDiag(QWidget *parent, babel::UIManager &uiManager);
    ~ReceiveCallDiag();

    void        setNameCallingText(std::string const& dataText);

    QPushButton *getDeclineButton();
    QPushButton *getAcceptButton();
    QLabel      *getNameCallingText();

public slots:
    void DecliningCall();
    void AcceptingCall();

private:
    std::shared_ptr<Ui::ReceiveCallDiag>    _ui;
    babel::UIManager                        &_uiManager;
};

#endif // RECEIVECALLDIAG_H
