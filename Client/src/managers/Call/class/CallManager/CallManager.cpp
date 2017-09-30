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

babel::Call & babel::CallManager::getCurrentCall(void)
{
	return this->_currentCall;
}

const babel::Status babel::CallManager::addNewParticipant(const std::string &)
{
	// TODO: network call to add a new participant to the call
	return babel::Status(0, "New participant added");
}

const babel::Status babel::CallManager::leaveCall(void)
{
    // TODO: Encapsulate this in network call (handlecmd)
	this->resetCurrentCall();
	// __________________________________________________
	return babel::Status(0, "Call ended");
}

const babel::Status babel::CallManager::joinCall(const std::unordered_map<std::string, babel::CallTunnel>& list)
{
	// TODO: Encapsulate this in network call
	this->_currentCall.updateParticipantsList(list);
	this->_currentCall.setActivity(true);
	// _________________________________________
	return babel::Status(0, "Call joined");
}

const std::unordered_map<std::string, babel::CallTunnel>& babel::CallManager::updateCurrentCallParticipants(void)
{
	// TODO : Netork call 'server.getParticipantForCall()'
	return this->_currentCall.getParticipants();
}

void babel::CallManager::resetCurrentCall(void)
{
	this->_currentCall.reset();
}
