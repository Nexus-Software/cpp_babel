/*
** HandleCmd.hpp for Server in /home/enguerrand/delivery/Server/HandleCmd.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 21:14:07 2017 Enguerrand Allamel
** Last update sam. sept. 23 21:14:07 2017 Enguerrand Allamel
*/

#ifndef SERVER_HANDLECMD_HPP
#define SERVER_HANDLECMD_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include "../Network/Protocol/NetworkData.hpp"
#include "Interfaces/ICmd.hpp"
#include "Cmd/CmdSignUp.hpp"
#include "Cmd/CmdLogIn.hpp"
#include "Cmd/CmdContactDelete.hpp"
#include "BabelNetworkMacro.hpp"

namespace babel
{
  class Server;

  class HandleCmd
  {
   protected:
    Server							&_server;
    std::unordered_map<std::uint32_t, std::shared_ptr<ICmd>> 	_cmdList;
   public:
    HandleCmd(Server &server);
    ~HandleCmd();

    bool execCmd(size_t tunnelId, NetworkData data);
  };
}

#endif //SERVER_HANDLECMD_HPP
