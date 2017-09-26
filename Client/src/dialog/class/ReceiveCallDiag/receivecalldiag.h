#ifndef RECEIVECALLDIAG_H
#define RECEIVECALLDIAG_H

#include <QDialog>

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

private:
    Ui::ReceiveCallDiag *_ui;
    babel::UIManager &_uiManager;
};

#endif // RECEIVECALLDIAG_H
