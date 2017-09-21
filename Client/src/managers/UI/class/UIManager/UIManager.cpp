#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager() {
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}