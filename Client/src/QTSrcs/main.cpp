#include "./include/QTHeaders/mainwindow.h"
#include "./include/QTHeaders/receivecalldiag.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    ReceiveCallDiag rCallDiag;

    win.show();
    rCallDiag.show();

    return a.exec();
}
