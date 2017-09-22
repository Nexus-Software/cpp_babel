#ifndef CUSTOMNOTIFICATIONDIAG_H
#define CUSTOMNOTIFICATIONDIAG_H

#include <QDialog>

namespace Ui {
class CustomNotificationDiag;
}

class CustomNotificationDiag : public QDialog
{
    Q_OBJECT

public:
    explicit CustomNotificationDiag(QWidget *parent = 0);
    ~CustomNotificationDiag();

private:
    Ui::CustomNotificationDiag *ui;
};

#endif // CUSTOMNOTIFICATIONDIAG_H
