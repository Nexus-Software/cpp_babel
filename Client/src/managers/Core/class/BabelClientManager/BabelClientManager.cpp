#include <iostream>
#include "BabelClientManager.hpp"

babel::BabelClientManager::BabelClientManager() {
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

const babel::Status babel::BabelClientManager::run(void)
{
	return babel::Status(0, "Everything is right!");
}
