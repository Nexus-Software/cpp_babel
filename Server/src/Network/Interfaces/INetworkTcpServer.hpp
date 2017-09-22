/*
** INetworkTcpServer.hpp for Server in /home/enguerrand/delivery/Server/INetworkTcpServer.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 20 18:27:53 2017 Enguerrand Allamel
** Last update mer. sept. 20 18:27:53 2017 Enguerrand Allamel
*/

#ifndef SERVER_INETWORKTCPSERVER_HPP
#define SERVER_INETWORKTCPSERVER_HPP

#include "INetworkTcpServerTunnel.hpp"

namespace babel {
  class INetworkTcpServer {
   public:
    virtual void waitClient() = 0;
  };
}

#endif //SERVER_INETWORKTCPSERVER_HPP
