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

babel::Server::Server(unsigned int port) :
	_port(port)
{
  this->_logInTerm.print("Server initialisation ...", LogInTerm::LevelLog::INFO);
}

babel::Server::~Server()
{

}

void babel::Server::run()
{
  this->_logInTerm.print("Server run", LogInTerm::LevelLog::SUCCESS);
  return ;
}