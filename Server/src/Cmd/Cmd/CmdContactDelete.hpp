/*
** CmdContactDelete.hpp for Server in /home/enguerrand/delivery/Server/CmdContactDelete.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 09:38:01 2017 Enguerrand Allamel
** Last update mer. sept. 27 09:38:01 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDCONTACTDELETE_HPP
#define SERVER_CMDCONTACTDELETE_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdContactDelete : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdContactDelete(Server &server);
    virtual ~CmdContactDelete();

    virtual bool run(size_t tunnelId,  NetworkData data);
  };
}

#endif //SERVER_CMDCONTACTDELETE_HPP
