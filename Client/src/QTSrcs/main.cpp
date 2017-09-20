#include "mainwindow.h"
#include "receivecalldiag.h"
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
