/*
** CmdSignUp.hpp for Server in /home/enguerrand/delivery/Server/CmdSignUp.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  lun. sept. 25 10:04:03 2017 Enguerrand Allamel
** Last update lun. sept. 25 10:04:03 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDSIGNUP_HPP
#define SERVER_CMDSIGNUP_HPP

#include "../HandleCmd.hpp"

namespace babel
{
  class Server;
  class CmdSignUp : public ICmd
  {
   protected:
    Server	&_server;
   public:
    CmdSignUp(Server &server);
    virtual ~CmdSignUp();

    virtual bool run(size_t tunnelId, NetworkData data);
  };
}

#endif //SERVER_CMDSIGNUP_HPP
