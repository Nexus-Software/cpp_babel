/*
** CmdSignUp.cpp for Server in /home/enguerrand/delivery/Server/CmdSignUp.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  lun. sept. 25 10:04:03 2017 Enguerrand Allamel
** Last update lun. sept. 25 10:04:03 2017 Enguerrand Allamel
*/

#include "CmdSignUp.hpp"
#include "Server.hpp"

babel::CmdSignUp::CmdSignUp(babel::Server &server) :
	_server(server)
{
}

babel::CmdSignUp::~CmdSignUp()
{
}

bool babel::CmdSignUp::run(size_t tunnelId,  NetworkData & data)
{
  std::string login(data.data.begin());
  std::string password(data.data.begin() + 32);

  std::cout << "Login: " << login << " - Password: " << password << std::endl;

  if (!this->_server.getAccountManager().add(login, password))
    {
      try
	{

	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(502, 0, {}));
	}
      catch (NetworkManagerException)
	{
	  this->_server.getLogInTerm().print("Tunnel id not found", LogInTerm::LevelLog::WARNING);
	}
      return false;
    }

  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setLogin(login);
  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setIsAuth(true);

  if (!this->_server.getAccountManager().login(login))
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(503, 0, {}));
      return false;
    }

  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(45, 0, {}));

  try
    {
      this->_server.getAccountManager().sendContactList(tunnelId,
							this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login);
    }
  catch (NetworkManagerException)
	  {
		  this->_server.getLogInTerm().print("Tunnel id not found", LogInTerm::LevelLog::WARNING);
	  }
  return true;
}
