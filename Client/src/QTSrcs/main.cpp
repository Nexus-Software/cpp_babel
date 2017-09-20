#include "./include/QTHeaders/mainwindow.h"
#include "./include/QTHeaders/receivecalldiag.h"
#include "./include/QTHeaders/logindiag.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    ReceiveCallDiag rCallDiag;
    LoginDiag loginDiag;

    win.show();
    rCallDiag.show();
    loginDiag.show();

    return a.exec();
}
