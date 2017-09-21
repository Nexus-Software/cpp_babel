#include <iostream>
#include "BabelClientManager.hpp"

babel::BabelClientManager::BabelClientManager() {
	std::cout << "BabelClientManager created" << std::endl;
}

babel::BabelClientManager::~BabelClientManager() {
	std::cout << "BabelClientManager destructed" << std::endl;
}
