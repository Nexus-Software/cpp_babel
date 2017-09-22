#ifndef ADDCONTACTDIAG_H
#define ADDCONTACTDIAG_H

#include <QDialog>

namespace Ui {
class AddContactDiag;
}

class AddContactDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDiag(QWidget *parent = 0);
    ~AddContactDiag();

private:
    Ui::AddContactDiag *ui;
};

#endif // ADDCONTACTDIAG_H
