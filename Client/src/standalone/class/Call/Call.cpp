#include "Call.hpp"

babel::Call::Call()
	:
	_isActive(false),
	_isMute(false)
{
	std::cout << "Call created" << std::endl;
}

babel::Call::Call(const babel::Call & item)
	:
	_participants(item.getParticipants()),
	_isActive(item.getActivity()),
	_isMute(item.isMute())
{

}

babel::Call::~Call()
{
	std::cout << "Call destructed" << std::endl;
}

const std::unordered_map<std::string, babel::CallTunnel>& babel::Call::getParticipants(void) const
{
	return this->_participants;
}

std::unordered_map<std::string, babel::CallTunnel>& babel::Call::getParticipants(void)
{
	return this->_participants;
}

const bool babel::Call::getActivity(void) const
{
	return this->_isActive;
}

const bool babel::Call::isMute(void) const
{
	return this->_isMute;
}

void babel::Call::setActivity(const bool activity)
{
	this->_isActive = activity;
}

void babel::Call::mute(void)
{
	this->setMute(true);
}

void babel::Call::unmute(void)
{
	this->setMute(false);
}

void babel::Call::reset(void)
{
	this->_participants.clear();
	this->unmute();
	this->setActivity(false);
}

const std::unordered_map<std::string, babel::CallTunnel>& babel::Call::updateParticipantsList(const std::unordered_map<std::string, babel::CallTunnel>& list)
{
	this->_participants = list;
	return this->_participants;
}

void babel::Call::setMute(const bool mute)
{
	this->_isMute = mute;
}

std::ostream& operator<<(std::ostream& os, const babel::Call& cl)
{
	unsigned int psize = cl.getParticipants().size();
	std::cout << "There is " << psize << " particpants in the call:" << std::endl;
	for (auto it : cl.getParticipants())
	{
        std::cout << it.second.login << std::endl;
	}
	return os;
}
