#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "UIManager.hpp"

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

    QListWidget *getFriendsList();

public slots:
    void OpenAddContactWindow();

private:
    Ui::MainWindow *_ui;
    babel::UIManager *_uiManager;
};

#endif // MAINWINDOW_H
