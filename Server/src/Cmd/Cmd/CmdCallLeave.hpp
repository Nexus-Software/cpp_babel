/*
** CmdCallLeave.hpp for Server in /home/enguerrand/delivery/Server/CmdCallLeave.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 30 18:11:16 2017 Enguerrand Allamel
** Last update sam. sept. 30 18:11:16 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDCALLLEAVE_HPP
#define SERVER_CMDCALLLEAVE_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdCallLeave : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdCallLeave(Server &server);
    virtual ~CmdCallLeave();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}

#endif //SERVER_CMDCALLLEAVE_HPP
