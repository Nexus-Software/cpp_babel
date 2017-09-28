/*
** CmdContactAdd.hpp for Server in /home/enguerrand/delivery/Server/CmdContactAdd.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 09:51:38 2017 Enguerrand Allamel
** Last update mer. sept. 27 09:51:38 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDCONTACTADD_HPP
#define SERVER_CMDCONTACTADD_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdContactAdd : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdContactAdd(Server &server);
    virtual ~CmdContactAdd();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}

#endif //SERVER_CMDCONTACTADD_HPP
