#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager(babel::BabelClientManager& ancestor)
:
    _root(ancestor),
    _widgetList({
        {"AddContactDiag", std::make_shared<AddContactDiag>()},
        {"CustomNotificationDiag", std::make_shared<CustomNotificationDiag>()},
        {"LoginDiag", std::make_shared<LoginDiag>()},
        {"MainWindow", std::make_shared<MainWindow>()},
        {"ReceiveCallDiag", std::make_shared<ReceiveCallDiag>()},
        {"SignupDiag", std::make_shared<SignupDiag>()}
    })
{
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}

babel::Status const                                                 babel::UIManager::start(std::string const &)
{
    for (auto it : this->_widgetList)
        this->_widgetList[it.first]->show();
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

std::unordered_map<std::string, std::shared_ptr<QWidget>>           &babel::UIManager::getWidgetList()
{
    return (this->_widgetList);
}
