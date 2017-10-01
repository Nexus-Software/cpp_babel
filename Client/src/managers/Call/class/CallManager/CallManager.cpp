#include "CallManager.hpp"

babel::CallManager::CallManager(babel::BabelClientManager& ancestor)
	:
	_root(ancestor)
{
	std::cout << "Call manager created" << std::endl;
}

babel::CallManager::~CallManager()
{
	std::cout << "Call manager destructed" << std::endl;
}

const bool&     babel::CallManager::isOwner(void) const
{
    return this->_isOwner;
}

babel::BabelClientManager& babel::CallManager::getRoot(void)
{
	return this->_root;
}

const babel::BabelClientManager& babel::CallManager::getRoot(void) const
{
	return this->_root;
}

const babel::Call & babel::CallManager::getCurrentcall(void) const
{
	return this->_currentCall;
}

void babel::CallManager::setOwner(const bool owner)
{
    this->_isOwner = owner;
}

babel::Call & babel::CallManager::getCurrentCall(void)
{
	return this->_currentCall;
}

const babel::Status	babel::CallManager::addNewParticipant(const babel::CallTunnel& usr)
{
	auto list = this->_currentCall.getParticipants();
	list.insert(std::pair<std::string, babel::CallTunnel>(usr.login, usr));
	this->updateCurrentCallParticipants(list);
	std::cout << "CALL MANAGER: New participant joined the call: " << usr.login << " (" << usr.ip << ":" << usr.port << ")" << std::endl;
	return babel::Status(0, "New participant added");
}

const babel::Status babel::CallManager::leaveCall(void)
{
	this->resetCurrentCall();
	return babel::Status(0, "Call ended");
}

void babel::CallManager::updateCurrentCallParticipants(const std::unordered_map<std::string, babel::CallTunnel>& prs)
{
	std::cout << "CALL MANAGER: Updating participant list:" << std::endl;
	for (auto it : prs) {
		std::cout << "--> " << it.second.login << " [" << it.second.ip << ":" << it.second.port << "]" << std::endl;
	}
	this->_currentCall.updateParticipantsList(prs);
}

void babel::CallManager::resetCurrentCall(void)
{
	this->_currentCall.reset();
}
