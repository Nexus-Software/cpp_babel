/*
** Call.cpp for Server in /home/enguerrand/delivery/Server/Call.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 14:09:40 2017 Enguerrand Allamel
** Last update mer. sept. 27 14:09:40 2017 Enguerrand Allamel
*/

#include "Call.hpp"
#include "Server.hpp"

babel::Call::Call(size_t id):
	_id(id)
{
}

babel::Call::~Call()
{
}

bool babel::Call::add(std::string login, babel::CallTunnel callTunnel)
{
  this->_participants.insert(std::pair<std::string, CallTunnel>(login, callTunnel));
  return true;
}

bool babel::Call::remove(std::string login)
{
  auto it = this->_participants.find(login);
  if (it == this->_participants.end())
    return false;
  this->_participants.erase(it);
  return true;
}

size_t babel::Call::getId() const
{
  return this->_id;
}

const std::unordered_map<std::string, babel::CallTunnel> &babel::Call::getParticipants() const
{
  return this->_participants;
}
