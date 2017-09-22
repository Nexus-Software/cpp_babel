#include "./include/QTHeaders/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_receivecalldiag.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 30 << 350;
    ui->WindowSplitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete ui;
}
