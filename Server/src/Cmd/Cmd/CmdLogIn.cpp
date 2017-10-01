/*
** CmdLogIn.cpp for Server in /home/enguerrand/delivery/Server/CmdLogIn.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  lun. sept. 25 12:08:30 2017 Enguerrand Allamel
** Last update lun. sept. 25 12:08:30 2017 Enguerrand Allamel
*/

#include "CmdLogIn.hpp"
#include "Server.hpp"

babel::CmdLogIn::CmdLogIn(babel::Server &server):
	_server(server)
{

}

babel::CmdLogIn::~CmdLogIn()
{

}

bool babel::CmdLogIn::run(size_t tunnelId,  NetworkData & data)
{
  std::string login(data.data.data());
  std::string password(data.data.data() + 32);

  std::cout << "Login: " << login << " - Password: " << password << std::endl;

  try
    {
      if (this->_server.getAccountManager().getAccountByLogin(login).getPassword() == password)
	{
	  if (!this->_server.getAccountManager().login(login))
	    {
	      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(503, 0, {}));
	      return false;
	    }
	  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setLogin(login);
	  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setIsAuth(true);

	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(44, 0, {}));

	  this->_server.getAccountManager().sendContactList(tunnelId,
							    this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(
								    tunnelId).login);
	  return true;
	}
    }
  catch (AccountManagerException)
    {
    }
  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(503, 0, {}));
  return false;
}
