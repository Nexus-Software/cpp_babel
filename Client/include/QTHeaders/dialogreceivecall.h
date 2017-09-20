#ifndef DIALOGRECEIVECALL_H
#define DIALOGRECEIVECALL_H

#include <QDialog>

namespace Ui {
class DialogReceiveCall;
}

class DialogReceiveCall : public QDialog
{
    Q_OBJECT

public:
    explicit DialogReceiveCall(QWidget *parent = 0);
    ~DialogReceiveCall();

private:
    Ui::DialogReceiveCall *ui;
};

#endif // DIALOGRECEIVECALL_H
