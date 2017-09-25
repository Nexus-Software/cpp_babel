#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

namespace babel {
    class UIManager;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, babel::UIManager *uiManager = 0);
    ~MainWindow();

private:
    Ui::MainWindow *_ui;
    babel::UIManager *_uiManager;
};

#endif // MAINWINDOW_H
