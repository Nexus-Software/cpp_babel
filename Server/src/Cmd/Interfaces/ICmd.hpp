/*
** ICmd.hpp for Server in /home/enguerrand/delivery/Server/ICmd.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 21:23:02 2017 Enguerrand Allamel
** Last update sam. sept. 23 21:23:02 2017 Enguerrand Allamel
*/

#ifndef SERVER_ICMD_HPP
#define SERVER_ICMD_HPP

#include <vector>
#include "BabelNetworkMacro.hpp"

namespace babel
{
  class ICmd
  {
   public:
    virtual bool run(size_t tunnelId, NetworkData & data) = 0;
  };
}

#endif //SERVER_ICMD_HPP
