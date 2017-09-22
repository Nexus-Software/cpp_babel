#include <iostream>
#include "AudioManager.hpp"

babel::AudioManager::AudioManager() {
	std::cout << "AudioManager created" << std::endl;
}

babel::AudioManager::~AudioManager() {
	std::cout << "AudioManager destructed" << std::endl;
}