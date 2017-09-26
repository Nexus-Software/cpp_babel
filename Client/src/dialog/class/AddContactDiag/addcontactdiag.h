#ifndef ADDCONTACTDIAG_H
#define ADDCONTACTDIAG_H

#include <QDialog>
#include <QListWidget>
#include "UIManager.hpp"

namespace Ui {
class AddContactDiag;
}

namespace babel {
    class UIManager;
}

class AddContactDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddContactDiag(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~AddContactDiag();

public slots:
    void AddSelectedContact();
    void CloseContactWindow();

private:
    Ui::AddContactDiag  *_ui;
    babel::UIManager    *_uiManager;
};

#endif // ADDCONTACTDIAG_H
