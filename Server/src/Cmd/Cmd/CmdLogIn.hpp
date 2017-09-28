/*
** CmdLogIn.hpp for Server in /home/enguerrand/delivery/Server/CmdLogIn.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  lun. sept. 25 12:08:30 2017 Enguerrand Allamel
** Last update lun. sept. 25 12:08:30 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDLOGIN_HPP
#define SERVER_CMDLOGIN_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdLogIn : public ICmd
  {
   protected:
    Server &_server;
   public:
    CmdLogIn(Server &server);
    virtual ~CmdLogIn();

    virtual bool run(size_t tunnelId,  NetworkData & data);
  };
}

#endif //SERVER_CMDLOGIN_HPP
