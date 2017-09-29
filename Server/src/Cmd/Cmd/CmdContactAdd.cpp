/*
** CmdContactAdd.cpp for Server in /home/enguerrand/delivery/Server/CmdContactAdd.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 09:51:38 2017 Enguerrand Allamel
** Last update mer. sept. 27 09:51:38 2017 Enguerrand Allamel
*/

#include "CmdContactAdd.hpp"
#include "Server.hpp"


babel::CmdContactAdd::CmdContactAdd(babel::Server &server):
	_server(server)
{
}

babel::CmdContactAdd::~CmdContactAdd()
{
}

bool babel::CmdContactAdd::run(size_t tunnelId, babel::NetworkData & data)
{
  std::string login(data.data.begin());

  std::cout << "Login: " << login << std::endl;

  try
    {
      if (!this->_server.getAccountManager().addContact(
	      this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login,
	      login))
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(506, 0, {}));
	  return false;
	}
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(47, 0, {}));

      this->_server.getAccountManager().sendContactList(tunnelId,
							this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login);

      return true;
    }
  catch (AccountManagerException & e)
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(506, 0, {}));
      return false;
    }
}