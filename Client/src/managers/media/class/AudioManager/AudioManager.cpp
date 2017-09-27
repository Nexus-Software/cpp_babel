#include <iostream>
#include "AudioManager.hpp"
#include "GlobalMediaManager.hpp"

babel::AudioManager::AudioManager(babel::GlobalMediaManager& ancestor)
:
	_parent(ancestor)
{
	std::cout << "AudioManager created" << std::endl;
}

babel::AudioManager::~AudioManager() {
	std::cout << "AudioManager destructed" << std::endl;
}

babel::GlobalMediaManager& babel::AudioManager::getParent() const
{
	return this->_parent;
}

bool babel::AudioManager::playSound(void)
{
	return false;
}

bool babel::AudioManager::getSound(void)
{
	return false;
}

bool babel::AudioManager::encodeSound(void)
{
	return false;
}

bool babel::AudioManager::decodeSound(void)
{
	return false;
}