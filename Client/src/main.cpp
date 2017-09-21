#include "./include/QTHeaders/mainwindow.h"
#include "./include/QTHeaders/receivecalldiag.h"
#include "./include/QTHeaders/logindiag.h"
#include "./include/QTHeaders/signupdiag.h"
#include "./include/QTHeaders/addcontactdiag.h"
#include "./include/QTHeaders/customnotificationdiag.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    ReceiveCallDiag rCallDiag;
    LoginDiag loginDiag;
    SignupDiag signupDiag;
    AddContactDiag addContactDiag;
    CustomNotificationDiag notificationDiag;

    win.show();
    rCallDiag.show();
    loginDiag.show();
    signupDiag.show();
    addContactDiag.show();
    notificationDiag.show();

    return a.exec();
}
