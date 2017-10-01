/*
** Call.hpp for Server in /home/enguerrand/delivery/Server/Call.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 14:09:40 2017 Enguerrand Allamel
** Last update mer. sept. 27 14:09:40 2017 Enguerrand Allamel
*/

#ifndef SERVER_CALL_HPP
#define SERVER_CALL_HPP

#include <string>
#include <unordered_map>

namespace babel
{
  struct CallTunnel
  {
    CallTunnel(std::string ip, unsigned int port, std::string login): ip(ip), port(port), login(login) {}
    std::string		login;
    std::string		ip;
    unsigned int	port;
  };
  class Call
  {
   private:
    size_t 					_id;
    std::unordered_map<std::string, CallTunnel>	_participants;
   public:
    Call(size_t id);
    virtual ~Call();

    bool add(std::string login, CallTunnel callTunnel);
    bool remove(std::string login);

    size_t getId() const;
    const std::unordered_map<std::string, CallTunnel> &getParticipants() const;
  };
}

#endif //SERVER_CALL_HPP
