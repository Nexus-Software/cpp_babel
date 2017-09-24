/*
** Server.cpp for Server in /home/enguerrand/delivery/Server/Server.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 20 18:51:53 2017 Enguerrand Allamel
** Last update mer. sept. 20 18:51:53 2017 Enguerrand Allamel
*/

#include "Server.hpp"
#include "Network/Boost/NetworkManagerBoost.hpp"


babel::Server::Server(unsigned int port) :
	_port(port),
	_handleCmd(*this)
{
  this->_logInTerm.print("Server initialisation ...", LogInTerm::LevelLog::INFO);
}

babel::Server::~Server()
{

}

void babel::Server::run()
{
  this->_logInTerm.print("Server run", LogInTerm::LevelLog::SUCCESS);

  this->_networkManager = std::make_shared<NetworkManagerBoost>(*this, this->_port);
  this->_networkManager.get()->acceptClient();
  while (1);
  return ;
}

const babel::LogInTerm & babel::Server::getLogInTerm() const
{
  return this->_logInTerm;
}
