/*
** CmdLeave.hpp for Server in /home/enguerrand/delivery/Server/CmdLeave.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 30 14:49:51 2017 Enguerrand Allamel
** Last update sam. sept. 30 14:49:51 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDLEAVE_HPP
#define SERVER_CMDLEAVE_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdLeave : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdLeave(Server &server);
    virtual ~CmdLeave();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}


#endif //SERVER_CMDLEAVE_HPP
