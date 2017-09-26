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

bool babel::CmdSignUp::run(size_t tunnelId,  NetworkData data)
{
  std::string dataToString(reinterpret_cast<const char *>(data.data.data()), 64);

  std::string login(dataToString.begin(), dataToString.begin() + 31);
  std::string password(dataToString.begin() + 32, dataToString.end());

  std::cout << "Login: " << login << " - Password: " << password << std::endl;

  if (!this->_server.getAccountManager().add(login, password))
    {
      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(502, 0, {}));
      return false;
    }

  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setLogin(login);
  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setIsAuth(true);
  this->_server.getAccountManager().getAccountByLogin(login).setIsOnline(true);

  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(42, 0, {}));
  return true;
}
