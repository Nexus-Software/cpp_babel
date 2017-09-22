#include <iostream>
#include "NetworkManager.hpp"

babel::NetworkManager::NetworkManager() {
	std::cout << "NetworkManager created" << std::endl;
}

babel::NetworkManager::~NetworkManager() {
	std::cout << "NetworkManager destructed" << std::endl;
}