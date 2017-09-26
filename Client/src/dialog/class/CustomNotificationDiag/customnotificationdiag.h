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
    explicit CustomNotificationDiag(QWidget *parent, babel::UIManager &uiManager);
    ~CustomNotificationDiag();

    void                setDataText(QString const& dataText);
    QString const       getDataText() const;

private:
    Ui::CustomNotificationDiag *_ui;
    babel::UIManager &_uiManager;
};

#endif // CUSTOMNOTIFICATIONDIAG_H
