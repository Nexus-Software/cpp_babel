/*
** HandleCmd.cpp for Server in /home/enguerrand/delivery/Server/HandleCmd.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 21:14:06 2017 Enguerrand Allamel
** Last update sam. sept. 23 21:14:06 2017 Enguerrand Allamel
*/

#include "HandleCmd.hpp"
#include "Server.hpp"

babel::HandleCmd::HandleCmd(babel::Server &server):
	_server(server),
	_cmdList({
			 {1, std::make_shared<CmdSignUp>(this->_server)},
			 {2, std::make_shared<CmdLogIn>(this->_server)},
			 {3, std::make_shared<CmdContactDelete>(this->_server)},
			 {4, std::make_shared<CmdContactAdd>(this->_server)},
			 {5, std::make_shared<CmdLeave>(this->_server)},
			 {7, std::make_shared<CmdCallInvite>(this->_server)},
			 {8, std::make_shared<CmdCallLeave>(this->_server)},
			 {9, std::make_shared<CmdCallJoin>(this->_server)}
		 })
{
}

babel::HandleCmd::~HandleCmd()
{

}

bool babel::HandleCmd::execCmd(size_t tunnelId, NetworkData & data)
{
  std::unordered_map<std::uint32_t, std::shared_ptr<ICmd>>::iterator it;

  if ((it = this->_cmdList.find(data.code)) != this->_cmdList.end())
    {
      try
	{
	  if (it->first > 2 && !this->_server.getNetworkManager().get()->getTunnelInfoByTunnelId(tunnelId).isAuth)
	    {
	      this->_server.getNetworkManager().get()->write(tunnelId, NetworkData(501, 0, {}));
	      return false;
	    }
	}
      catch (NetworkManagerException)
	{
	  this->_server.getLogInTerm().print("(HandleCMD): Tunnel id not found into", LogInTerm::LevelLog::WARNING);
	  return false;
	}
      (*it).second.get()->run(tunnelId, data);
      std::cout << "CMD: N:" << it->first << std::endl;
      return true;
    }
  return false;
}
