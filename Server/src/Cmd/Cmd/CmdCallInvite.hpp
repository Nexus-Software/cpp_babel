/*
** CmdCallInvite.hpp for Server in /home/enguerrand/delivery/Server/CmdCallInvite.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 28 22:04:27 2017 Enguerrand Allamel
** Last update jeu. sept. 28 22:04:27 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDCALLINVITE_HPP
#define SERVER_CMDCALLINVITE_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdCallInvite : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdCallInvite(Server &server);
    virtual ~CmdCallInvite();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}

#endif //SERVER_CMDCALLINVITE_HPP
