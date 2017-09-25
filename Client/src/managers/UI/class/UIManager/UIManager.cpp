#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager(babel::BabelClientManager& ancestor)
:
    _root(ancestor),
    _windowList({
        {"AddContactDiag", std::make_shared<AddContactDiag>(nullptr, this)},
        {"CustomNotificationDiag", std::make_shared<CustomNotificationDiag>(nullptr, this)},
        {"LoginDiag", std::make_shared<LoginDiag>(nullptr, this)},
        {"MainWindow", std::make_shared<MainWindow>(nullptr, this)},
        {"ReceiveCallDiag", std::make_shared<ReceiveCallDiag>(nullptr, this)},
        {"SignupDiag", std::make_shared<SignupDiag>(nullptr, this)}
    })
{
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}

babel::Status const                                                 babel::UIManager::showWindow(std::string const& windowName)
{
    if (!this->_windowList[windowName])
        return (babel::Status(1, "Window couldn't be showed"));
    this->_windowList[windowName]->show();
    return (babel::Status(0, "Window '" + windowName + "' is now showed"));
}

babel::Status const                                                 babel::UIManager::hideWindow(std::string const& windowName)
{
    if (!this->_windowList[windowName])
        return (babel::Status(1, "Window couldn't be hidden"));
    this->_windowList[windowName]->hide();
    return (babel::Status(0, "Window '" + windowName + "' is now hidden"));
}

babel::Status const                                                 babel::UIManager::start()
{
    this->showWindow("LoginDiag");
    return (babel::Status(0, "UIManager 'start()' worked without error"));
}

babel::BabelClientManager                                           &babel::UIManager::getRoot()
{
    return (this->_root);
}

babel::BabelClientManager const                                     &babel::UIManager::getRoot() const
{
    return (this->_root);
}

std::unordered_map<std::string, std::shared_ptr<QWidget>>           &babel::UIManager::getWindowList()
{
    return (this->_windowList);
}
