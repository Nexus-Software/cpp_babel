#include <iostream>
#include "UIManager.hpp"

babel::UIManager::UIManager(babel::BabelClientManager& ancestor)
:
	_root(ancestor)
{
	std::cout << "UIManager created" << std::endl;
}

babel::UIManager::~UIManager() {
	std::cout << "UIManager destructed" << std::endl;
}