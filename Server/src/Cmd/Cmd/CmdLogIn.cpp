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

bool babel::CmdLogIn::run(size_t tunnelId, char *data)
{
  std::string dataToString(reinterpret_cast<const char *>(data), 64);

  std::string login(dataToString.begin(), dataToString.begin() + 31);
  std::string password(dataToString.begin() + 32, dataToString.end());

  std::cout << "Login: " << login << " - Password: " << password << std::endl;

  // Todo: Check login not register + pass not valid if error is throw

  if (this->_server.getAccountManager().getAccountByLogin(login).getPassword() == password)
    {
      this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setLogin(login);
      this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).setIsAuth(true);
      this->_server.getAccountManager().getAccountByLogin(login).setIsOnline(true);

      this->_server.getNetworkManager().get()->write(tunnelId, dataToWrite(42, 0, NULL));
      return true;
    }
  this->_server.getNetworkManager().get()->write(tunnelId, dataToWrite(503, 0, NULL));
  return false;
}
