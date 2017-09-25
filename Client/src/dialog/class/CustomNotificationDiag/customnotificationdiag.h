#ifndef CUSTOMNOTIFICATIONDIAG_H
#define CUSTOMNOTIFICATIONDIAG_H

#include <QDialog>

namespace Ui {
class CustomNotificationDiag;
}

namespace babel {
    class UIManager;
}

class CustomNotificationDiag : public QDialog
{
    Q_OBJECT

public:
    explicit CustomNotificationDiag(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~CustomNotificationDiag();

private:
    Ui::CustomNotificationDiag *_ui;
    babel::UIManager *_uiManager;
};

#endif // CUSTOMNOTIFICATIONDIAG_H
