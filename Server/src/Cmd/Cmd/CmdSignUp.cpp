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
  std::string login(data.data.begin(), data.data.begin() + 31);
  std::string password(data.data.begin() + 32, data.data.begin() + 64);

  std::cout << "Login: " << login << " - Password: " << password << std::endl;

  if (!this->_server.getAccountManager().add(login, password))
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(502, 0, {}));
      return false;
    }

  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setLogin(login);
  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setIsAuth(true);
  this->_server.getAccountManager().getAccountByLogin(login).setIsOnline(true);

  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(45, 0, {}));

  this->_server.getAccountManager().sendContactList(tunnelId,
						    this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login);
  return true;
}
