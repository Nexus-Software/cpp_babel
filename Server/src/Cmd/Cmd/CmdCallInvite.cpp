/*
** CmdCallInvite.cpp for Server in /home/enguerrand/delivery/Server/CmdCallInvite.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 28 22:04:27 2017 Enguerrand Allamel
** Last update jeu. sept. 28 22:04:27 2017 Enguerrand Allamel
*/

#include "CmdCallInvite.hpp"
#include "Server.hpp"

babel::CmdCallInvite::CmdCallInvite(babel::Server &server):
	_server(server)
{
}

babel::CmdCallInvite::~CmdCallInvite()
{

}

bool babel::CmdCallInvite::run(size_t tunnelId, babel::NetworkData &data)
{
  NetworkDataCSInvite networkDataCSInvite = {0};
  std::copy_n(reinterpret_cast<const char *>(&data.data), sizeof(NetworkDataCSInvite), reinterpret_cast<char *>(&networkDataCSInvite));

  if (!this->_server.getCallManager().convIsExist(networkDataCSInvite.idCall))
    return false;
  this->_server.getCallManager().invite(networkDataCSInvite.idCall, networkDataCSInvite.loginInvite);

  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(48, 0, {}));

  //Todo: Invite loginInvite
  return true;
}
