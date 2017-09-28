/*
** CmdCallJoin.hpp for Server in /home/enguerrand/delivery/Server/CmdCallJoin.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 16:43:05 2017 Enguerrand Allamel
** Last update mer. sept. 27 16:43:05 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDCALLJOIN_HPP
#define SERVER_CMDCALLJOIN_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdCallJoin : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdCallJoin(Server &server);
    virtual ~CmdCallJoin();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}

#endif //SERVER_CMDCALLJOIN_HPP
