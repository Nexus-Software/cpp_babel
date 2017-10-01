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
  std::string login(data.data.data());

  std::cout << "Login: " << login << std::endl;

  try
    {
      this->_server.getAccountManager().getAccountByLogin(login);
      if (login == this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login)
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(501, 0, {}));
	  return false;
	}
      else if (!this->_server.getAccountManager().addContact(
	      this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login,
	      login))
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(501, 0, {}));
	  return false;
	}
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(47, 0, {}));

      this->_server.getAccountManager().sendContactList(tunnelId,
							this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login);

      if (this->_server.getAccountManager().getAccountByLogin(login).getIsOnline())
	{
	  this->_server.getAccountManager().sendContactList(this->_server.getNetworkManager().get()->getTunnelIdByLogin(login),
							  login);
	}
      return true;
    }
  catch (AccountManagerException)
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(505, 0, {}));
      return false;
    }
  catch (NetworkManagerException)
    {
      return false;
    }
}