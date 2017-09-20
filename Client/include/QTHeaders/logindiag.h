#ifndef LOGINDIAG_H
#define LOGINDIAG_H

#include <QDialog>

namespace Ui {
class LoginDiag;
}

class LoginDiag : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDiag(QWidget *parent = 0);
    ~LoginDiag();

private:
    Ui::LoginDiag *ui;
};

#endif // LOGINDIAG_H
