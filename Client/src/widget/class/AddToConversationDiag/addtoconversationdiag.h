#ifndef ADDTOCONVERSATIONDIAG_H
#define ADDTOCONVERSATIONDIAG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include "UIManager.hpp"

namespace Ui {
class AddToConversationDiag;
}

namespace babel {
    class UIManager;
}

class AddToConversationDiag : public QDialog
{
    Q_OBJECT

public:
    explicit AddToConversationDiag(QWidget *parent, babel::UIManager &uiManager);
    ~AddToConversationDiag();

    QListWidget                 *getFriendsList() const;
    QLabel                      *getCurrentlySelectedLabel() const;
    QList<std::string>          &getTmpConversationList();

public slots:
    void    CancelActionAddToConversationWindow();
    void    ConfirmActionAddToConversationWindow();
    void    RefreshFriendsInConversation(QListWidgetItem *item);

private:
    Ui::AddToConversationDiag   *_ui;
    babel::UIManager            &_uiManager;
    QList<std::string>          _tmpConversationList;
};

#endif // ADDTOCONVERSATIONDIAG_H
