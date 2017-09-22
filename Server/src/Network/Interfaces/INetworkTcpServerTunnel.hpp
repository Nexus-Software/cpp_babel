/*
** INetworkTcpServerTunnel.hpp for Server in /home/enguerrand/delivery/Server/INetworkTcpServerTunnel.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 20 19:18:02 2017 Enguerrand Allamel
** Last update mer. sept. 20 19:18:02 2017 Enguerrand Allamel
*/

#ifndef SERVER_INETWORKTCPSERVERTUNNEL_HPP
#define SERVER_INETWORKTCPSERVERTUNNEL_HPP

#include "BabelNetwork.hpp"

namespace babel {
  class INetworkTcpServerTunnel
  {
   public:
    virtual void read(const unsigned int size) = 0;
    virtual void write(const unsigned int size, const char buffer[B_NETWORK_BUFFER_SIZE]) = 0;
    virtual const bool close() const = 0;
  };
}

#endif //SERVER_INETWORKTCPSERVERTUNNEL_HPP
