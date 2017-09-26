#include <iostream>
#include "NetworkManager.hpp"
#include "babelClientManager.hpp"

babel::NetworkManager::NetworkManager(babel::BabelClientManager& ancestor)
:
	_root(ancestor),
	_networkTcp(std::make_shared<babel::QNetworkTcpClient>())
{
	std::cout << "NetworkManager created" << std::endl;
	this->_networkTcp->connectToTcpHost(IP_VPS, 4546);
}

babel::NetworkManager::~NetworkManager() {
	std::cout << "NetworkManager destructed" << std::endl;
}

babel::BabelClientManager& babel::NetworkManager::getRoot() const
{
	return this->_root;
}

const std::shared_ptr<babel::INetworkTcpClient> babel::NetworkManager::getNetworkTcp() const
{
	return this->_networkTcp;
}

std::shared_ptr<babel::INetworkTcpClient> babel::NetworkManager::getNetworkTcp()
{
	return this->_networkTcp;
}