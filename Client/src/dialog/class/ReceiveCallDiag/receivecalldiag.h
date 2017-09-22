#ifndef RECEIVECALLDIAG_H
#define RECEIVECALLDIAG_H

#include <QDialog>

namespace Ui {
class ReceiveCallDiag;
}

class ReceiveCallDiag : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveCallDiag(QWidget *parent = 0);
    ~ReceiveCallDiag();

private:
    Ui::ReceiveCallDiag *ui;
};

#endif // RECEIVECALLDIAG_H
