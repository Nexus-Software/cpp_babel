#ifndef SIGNUPDIAG_H
#define SIGNUPDIAG_H

#include <QDialog>

namespace Ui {
    class SignupDiag;
}

class SignupDiag : public QDialog
{
    Q_OBJECT

public:
    explicit SignupDiag(QWidget *parent = 0);
    ~SignupDiag();

private:
    Ui::SignupDiag *_ui;
};

#endif // SIGNUPDIAG_H
