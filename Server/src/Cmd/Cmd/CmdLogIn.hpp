/*
** CmdLogin.hpp for Server in /home/enguerrand/delivery/Server/CmdLogin.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 21:39:07 2017 Enguerrand Allamel
** Last update sam. sept. 23 21:39:07 2017 Enguerrand Allamel
*/

#ifndef SERVER_CMDLOGIN_HPP
#define SERVER_CMDLOGIN_HPP

#include "../Interfaces/ICmd.hpp"

namespace babel
{
  class CmdLogIn : public ICmd
  {
   public:
    CmdLogIn();
    ~CmdLogIn();

    virtual bool run(std::vector<char> data);
  };
}

#endif //SERVER_CMDLOGIN_HPP
