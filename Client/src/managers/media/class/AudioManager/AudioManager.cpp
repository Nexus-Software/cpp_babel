#include <iostream>
#include "AudioManager.hpp"
#include "GlobalMediaManager.hpp"
#include "BabelClientManager.hpp"

babel::AudioManager::AudioManager(babel::GlobalMediaManager& ancestor)
	:
	_parent(ancestor),
	_run(false),
	_thread(nullptr)
{
	
}

babel::AudioManager::~AudioManager() {
	this->setStreamState(false);
	
}

babel::GlobalMediaManager& babel::AudioManager::getParent() const
{
	return this->_parent;
}

bool 	babel::AudioManager::playSound(B_SAMPLE sample)
{
	return this->_audio.play(sample);
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
	if (state) {
		this->_audio.startStream();
		this->_run = true;
		this->_thread = std::make_shared<std::thread>([&]() {
			B_SAMPLE in, out;
			babel::Codec codec;
			EncodedData data;
			std::mutex lock;

			while (this->_run) {
				lock.lock();
				B_SAMPLE in = this->recordSound();
				data = codec.Encode(in);
				this->_parent.getRoot().getNetwork().sendRecordToCall(data.data);
				//codec.Decode(data, out);
				//this->playSound(out);
				lock.unlock();
			}
		});
	}
	else {
		this->_run = false;
		if (this->_thread) {
			this->_thread->join();
			this->_thread.reset();
		}
			
		this->_audio.stopStream();
	}
		
}
