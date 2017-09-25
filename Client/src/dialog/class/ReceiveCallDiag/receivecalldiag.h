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
    explicit ReceiveCallDiag(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~ReceiveCallDiag();

private:
    Ui::ReceiveCallDiag *_ui;
    babel::UIManager *_uiManager;
};

#endif // RECEIVECALLDIAG_H
