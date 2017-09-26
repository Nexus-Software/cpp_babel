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
			 {2, std::make_shared<CmdLogIn>(this->_server)}
		})
{
}

babel::HandleCmd::~HandleCmd()
{

}

bool babel::HandleCmd::execCmd(size_t tunnelId, NetworkData data)
{
  /* dataToWrite data1;
  std::uint32_t nb = 32;
  data1.size = sizeof(std::uint32_t);
  data1.data = &nb;
  this->_server.getNetworkManager().get()->write(tunnelId, data1);
  nb = 342;
  data1.size = sizeof(std::uint32_t);
  data1.data = &nb;
  this->_server.getNetworkManager().get()->write(tunnelId, data1); */

  //Todo: Resend to Cmd code reponse

  std::unordered_map<std::uint32_t, std::shared_ptr<ICmd>>::iterator it;

  if ((it = this->_cmdList.find(data.code)) != this->_cmdList.end())
    {
      (*it).second.get()->run(tunnelId, data);
      std::cout << "CMD FOUND" << std::endl;
      return true;
    }
  std::cout << "CMD NOT FOUND" << std::endl;
  return false;
}
