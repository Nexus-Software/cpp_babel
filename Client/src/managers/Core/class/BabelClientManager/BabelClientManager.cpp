#include <iostream>
#include "BabelClientManager.hpp"

babel::BabelClientManager::BabelClientManager(int argc, char **argv)
:
    _app(argc, argv),
    _ui(*this),
    _argc(argc),
    _argv(argv)
{
	std::cout << "BabelClientManager created" << std::endl;
}

babel::BabelClientManager::~BabelClientManager() {
	std::cout << "BabelClientManager destructed" << std::endl;
}

const babel::GlobalMediaManager & babel::BabelClientManager::getMedia(void) const
{
    return this->_media;
}

const babel::UIManager & babel::BabelClientManager::getUI(void) const
{
    return this->_ui;
}

const babel::NetworkManager & babel::BabelClientManager::getNetwork(void) const
{
    return this->_network;
}

const babel::ContactManager & babel::BabelClientManager::getContact(void) const
{
    return this->_contact;
}

const babel::Call & babel::BabelClientManager::getCurrentCall(void) const
{
    return this->_currentCall;
}

babel::GlobalMediaManager & babel::BabelClientManager::getMedia(void)
{
    return this->_media;
}

babel::UIManager & babel::BabelClientManager::getUI(void)
{
    return this->_ui;
}

babel::NetworkManager & babel::BabelClientManager::getNetwork(void)
{
    return this->_network;
}

babel::ContactManager & babel::BabelClientManager::getContact(void)
{
    return this->_contact;
}

babel::Call &babel::BabelClientManager::getCurrentCall(void)
{
    return this->_currentCall;
}
const int   babel::BabelClientManager::getArgc(void) const
{
    return (this->_argc);
}

char        **babel::BabelClientManager::getArgv(void) const
{
    return (this->_argv);
}

QApplication    &babel::BabelClientManager::getApp(void)
{
    return (this->_app);
}

const QApplication    &babel::BabelClientManager::getApp(void) const
{
    return (this->_app);
}

const int babel::BabelClientManager::run(void)
{
    this->getUI().start("LoginDiag");
    return (this->_app.exec());
}
