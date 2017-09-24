/*
** INetworkManager.hpp for Server in /home/enguerrand/delivery/Server/INetworkManager.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 10:57:03 2017 Enguerrand Allamel
** Last update dim. sept. 24 10:57:03 2017 Enguerrand Allamel
*/

#ifndef SERVER_INETWORKMANAGER_HPP
#define SERVER_INETWORKMANAGER_HPP

#include <string>

namespace babel
{
  struct TunnelInfo
  {
    size_t 	id;
    std::string	login;
    bool 	isAuth;
  };

  struct dataToWrite
  {
    unsigned int 		size;
    void 			*data;
  };

  class INetworkManager
  {
   public:
    virtual void acceptClient() = 0;

    virtual bool write(size_t tunnelId, dataToWrite data) = 0;
    virtual bool write(std::string login, dataToWrite data) = 0;

    virtual bool writeForAll(dataToWrite data) = 0;

    virtual TunnelInfo getTunnelInfoByTunnelId(const size_t tunnelId) const = 0;
    virtual void setTunnelInfoByTunnelId(const size_t tunnelId, const TunnelInfo tunnelInfo) = 0;
  };
}

#endif //SERVER_INETWORKMANAGER_HPP
