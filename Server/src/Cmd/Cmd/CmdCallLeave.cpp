/*
** CmdCallLeave.cpp for Server in /home/enguerrand/delivery/Server/CmdCallLeave.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 30 18:11:16 2017 Enguerrand Allamel
** Last update sam. sept. 30 18:11:16 2017 Enguerrand Allamel
*/

#include "CmdCallLeave.hpp"
#include "Server.hpp"

babel::CmdCallLeave::CmdCallLeave(babel::Server &server):
	_server(server)
{
}

babel::CmdCallLeave::~CmdCallLeave()
{

}

bool babel::CmdCallLeave::run(size_t tunnelId, babel::NetworkData &data)
{
  std::uint32_t idCall = {0};
  std::copy_n(reinterpret_cast<const char *>(&data.data), sizeof(std::uint32_t), reinterpret_cast<char *>(&idCall));

  try
    {
      if (!this->_server.getCallManager().convIsExist(idCall))
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(506, 0, {}));
	  return false;
	}
      else if (this->_server.getCallManager().remove(idCall, this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(
	      tunnelId).login))
	{
	  this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(49, 0, {}));

	  std::array<char, 2048> dataLoginLeave = {0};
	  this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).login.copy(dataLoginLeave.begin(), 32);
	  auto participant = this->_server.getCallManager().getCalls().find(idCall)->second.getParticipants();
	  for (auto it : participant)
	    {
	      try
		{
		  this->_server.getNetworkManager().get()->write(it.second.login, NetworkData(8, 0, dataLoginLeave));
		}
	      catch (NetworkManagerException &e)
		{
		  continue ;
		}
	    }
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
