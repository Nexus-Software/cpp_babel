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

bool 	babel::AudioManager::playSound(B_SAMPLE sample, int size)
{
	return this->_audio.play(sample, size);
}

B_SAMPLE babel::AudioManager::recordSound(void)
{
	return this->_audio.record();
}

bool babel::AudioManager::encodeSound(void)
{
	return false;
}

bool babel::AudioManager::decodeSound(void)
{
	return false;
}
void babel::AudioManager::setStreamState(bool state)
{
	if (state)
		this->_audio.startStream();
	else
		this->_audio.stopStream();
}