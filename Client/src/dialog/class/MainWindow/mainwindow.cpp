#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, babel::UIManager &uiManager) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _uiManager(uiManager)
{
    this->_ui->setupUi(this);

    QList<int> sizes;
    sizes << 30 << 350;
    this->_ui->WindowSplitter->setSizes(sizes);

    QObject::connect(this->_ui->FilterFriendField, SIGNAL(textChanged(QString const&)), this, SLOT(FilterFriendsList(QString const&)));
    QObject::connect(this->_ui->ActionDisconnect, SIGNAL(triggered()), this, SLOT(RedirectToLoginDiag()));
    QObject::connect(this->_ui->ActionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(this->_ui->AddContactButton, SIGNAL(clicked()), this, SLOT(OpenAddContactWindow()));
}

MainWindow::~MainWindow()
{
    delete (this->_ui);
}

QListWidget             *MainWindow::getFriendsList()
{
    return (this->_ui->FriendsList);
}

QLabel                  *MainWindow::getGeneralInformations()
{
    return (this->_ui->GeneralInformations);
}

void                    MainWindow::FilterFriendsList(QString const& filterText)
{
    QList<QListWidgetItem *> filteredList = this->_ui->FriendsList->findItems(filterText, Qt::MatchContains);

    if (!filterText.isEmpty())
    {
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
            this->_ui->FriendsList->item(i)->setHidden(true);
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
        {
            for (int j = 0; j < filteredList.count(); j++)
            {
                if (this->_ui->FriendsList->item(i)->data(0).toString().toStdString() == filteredList[j]->data(0).toString().toStdString())
                    this->_ui->FriendsList->item(i)->setHidden(false);
            }
        }
    }
    else
    {
        for (int i = 0; i < this->_ui->FriendsList->count(); i++)
            this->_ui->FriendsList->item(i)->setHidden(false);
    }
}

void                    MainWindow::RedirectToLoginDiag()
{
    this->_uiManager.hideWindow("MainWindow");
    this->_uiManager.showWindow("LoginDiag");
}

void                    MainWindow::OpenAddContactWindow()
{
    this->_uiManager.showWindow("AddContactDiag");
    this->_ui->FilterFriendField->setText("");
}
