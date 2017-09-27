/*
** CallManager.cpp for Server in /home/enguerrand/delivery/Server/CallManager.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 14:05:05 2017 Enguerrand Allamel
** Last update mer. sept. 27 14:05:05 2017 Enguerrand Allamel
*/

#include "CallManager.hpp"
#include "Server.hpp"

babel::CallManager::CallManager(babel::Server &server):
	_server(server)
{
}

babel::CallManager::~CallManager()
{
}

bool babel::CallManager::invite(size_t idCall, std::string login)
{
  if (!this->convIsExist(idCall) || !this->_server.getAccountManager().getAccountByLogin(login).getIsOnline())
    return false;
  this->_pendingInvite.insert(std::pair<size_t, std::string>(idCall, login));
  return false;
}

bool babel::CallManager::add(size_t idCall, std::string login, std::string ip, unsigned int port)
{
  if (!this->convIsExist(idCall))
    return false;
  (*this->_calls.find(idCall)).second.add(login, CallTunnel(ip, port));

  /*
  CLIENT_CALL_STRUCT client;
  login.copy(client.login, 32);
  ip.copy(client.ip, 15);
  client.port = port;

  std::array<char, 2048> data;
  std::copy_n(reinterpret_cast<const char *>(&client), sizeof(CLIENT_CALL_STRUCT), data.begin());

  auto participant = (*this->_calls.find(idCall)).second.getParticipants();
  for (auto it = participant.begin() ; it != participant.end() ; it++)
    {
      this->_server.getNetworkManager().get()->write((*it).first, NetworkData(9, sizeof(CLIENT_CALL_STRUCT), data));
    }
    */

  return false;
}

bool babel::CallManager::remove(size_t idCall, std::string login)
{if (!this->convIsExist(idCall))
    return false;
  (*this->_calls.find(idCall)).second.remove(login);
  return false;
}

bool babel::CallManager::isAllowToJoin(size_t idCall, std::string login)
{
  if (!this->convIsExist(idCall))
    return false;
  for (auto it = this->_pendingInvite.begin() ; it != this->_pendingInvite.end() ; it++)
    {
      if ((*it).first == idCall && (*it).second.compare(login) == 0)
	return true;
    }
  return false;
}

bool babel::CallManager::convIsExist(size_t idCall)
{
  auto it = this->_calls.find(idCall);
  if (it != this->_calls.end())
    return true;
  return false;
}

babel::Call babel::CallManager::create()
{
  size_t minId = 0;
  for (auto it = this->_calls.begin() ; it != this->_calls.end() ; it++)
    {
      if ((*it).first == minId)
	{
	  minId += 1;
	  it = this->_calls.begin();
	}
    }
  return babel::Call(minId);
}

bool babel::CallManager::finish(size_t idCall)
{
  if (!this->convIsExist(idCall))
    return false;
  this->_calls.erase(idCall);
  return true;
}
