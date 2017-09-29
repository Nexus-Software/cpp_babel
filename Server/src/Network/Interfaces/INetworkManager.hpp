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
#include <array>
#include "../Protocol/NetworkData.hpp"

namespace babel
{
  struct TunnelInfo
  {
    size_t 	id;
    std::string	login;
    bool 	isAuth;
    std::string ip;

    void setId(size_t id) { this->id = id; };
    void setLogin(const std::string & login) { this->login = login; };
    void setIsAuth(bool isAuth) { this->isAuth = isAuth; };
    void setIp(const std::string & ip) { this->ip = ip; };
  };

  class INetworkManager
  {
   public:
    virtual void acceptClient() = 0;

    virtual bool write(size_t tunnelId, NetworkData data) = 0;
    virtual bool write(std::string login, NetworkData data) = 0;

    virtual bool writeForAll(NetworkData data) = 0;

    virtual TunnelInfo & getTunnelInfoByTunnelId(const size_t tunnelId) = 0;

    virtual void setIpForTunnelId(size_t tunnelId, const std::string & ip) = 0;
  };
}

#endif //SERVER_INETWORKMANAGER_HPP
