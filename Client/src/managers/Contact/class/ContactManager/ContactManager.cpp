#include <iostream>
#include "ContactManager.hpp"

babel::ContactManager::ContactManager()
{
	std::cout << "ContactManager created" << std::endl;
}

babel::ContactManager::~ContactManager()
{
	std::cout << "ContactManager destructed" << std::endl;
}