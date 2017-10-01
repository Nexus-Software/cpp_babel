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
  std::copy_n(data.data.data(), sizeof(NetworkDataCSInvite), reinterpret_cast<char *>(&networkDataCSInvite));

  try
    {
      std::cout << "Call ID INVITE: " << networkDataCSInvite.idCall << std::endl;
      std::cout << "Call Login Invite: " << networkDataCSInvite.loginInvite << std::endl;
      if (!this->_server.getCallManager().convIsExist(networkDataCSInvite.idCall))
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(506, 0, {}));
	  return false;
	}
      else if (this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login.compare(networkDataCSInvite.loginInvite) == 0 ||
	      this->_server.getCallManager().invite(networkDataCSInvite.idCall, networkDataCSInvite.loginInvite))
	{
	  NetworkDataSCInvite networkDataSCInvite = {0};

	  networkDataSCInvite.idCall = networkDataCSInvite.idCall;
	  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login.copy(networkDataSCInvite.loginHasInvite, 32);

	  Call call = this->_server.getCallManager().getCalls().find(networkDataCSInvite.idCall)->second;

	  int i = 0;
	  for (auto it : call.getParticipants())
	    {
	      std::cout << it.second.login << std::endl;
	      it.second.login.copy(networkDataSCInvite.clientInConv[i], 32);
	      i += 1;
	    }

	  std::cout << "LoginHasInvite: " << networkDataSCInvite.loginHasInvite << std::endl;
	  std::cout << "Login 1: " << networkDataSCInvite.clientInConv[0] << std::endl;

	  std::array<char, 2048> dataSend = {0};
	  std::copy_n(reinterpret_cast<const char *>(&networkDataSCInvite), sizeof(NetworkDataSCInvite), dataSend.begin());

	  this->_server.getNetworkManager().get()->write(networkDataCSInvite.loginInvite, NetworkData(7, 0, dataSend));
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(48, 0, {}));
	  return true;
	}
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
  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(505, 0, {}));
  return false;

}
