#include <iostream>
#include "VideoManager.hpp"

babel::VideoManager::VideoManager() {
	std::cout << "VideoManager created" << std::endl;
}

babel::VideoManager::~VideoManager() {
	std::cout << "VideoManager destructed" << std::endl;
}