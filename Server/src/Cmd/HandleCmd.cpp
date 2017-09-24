/*
** HandleCmd.cpp for Server in /home/enguerrand/delivery/Server/HandleCmd.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 21:14:06 2017 Enguerrand Allamel
** Last update sam. sept. 23 21:14:06 2017 Enguerrand Allamel
*/

#include "HandleCmd.hpp"
#include "Server.hpp"

babel::HandleCmd::HandleCmd(babel::Server &server):
	_server(server)
{
  this->_cmdList =
	  {
		  {2, std::make_shared<CmdLogIn>()}
	  };
}

babel::HandleCmd::~HandleCmd()
{

}

bool babel::HandleCmd::execCmd(size_t tunnelId, std::uint32_t code, char data[B_NETWORK_BUFFER_SIZE])
{
  dataToWrite data1;
  std::uint32_t nb = 32;
  data1.size = sizeof(std::uint32_t);
  data1.data = &nb;
  this->_server.getNetworkManager().get()->write(tunnelId, data1);
  nb = 342;
  data1.size = sizeof(std::uint32_t);
  data1.data = &nb;
  this->_server.getNetworkManager().get()->write(tunnelId, data1);
  // Todo: Not implement yet
  return true;
}
