/*
** CmdLeave.cpp for Server in /home/enguerrand/delivery/Server/CmdLeave.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 30 14:49:51 2017 Enguerrand Allamel
** Last update sam. sept. 30 14:49:51 2017 Enguerrand Allamel
*/

#include "CmdLeave.hpp"
#include "Server.hpp"

babel::CmdLeave::CmdLeave(babel::Server &server):
	_server(server)
{
}

babel::CmdLeave::~CmdLeave()
{

}

bool babel::CmdLeave::run(size_t, babel::NetworkData &)
{
  return true;
}
