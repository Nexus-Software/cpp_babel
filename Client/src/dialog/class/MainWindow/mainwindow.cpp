#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, babel::UIManager *uiManager) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);

    QList<int> sizes;
    sizes << 30 << 350;
    this->_ui->WindowSplitter->setSizes(sizes);
}

MainWindow::~MainWindow()
{
    delete (this->_ui);
}
