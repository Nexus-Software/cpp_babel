/*
** CallManager.hpp for Server in /home/enguerrand/delivery/Server/CallManager.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 27 14:05:05 2017 Enguerrand Allamel
** Last update mer. sept. 27 14:05:05 2017 Enguerrand Allamel
*/

#ifndef SERVER_CALLMANAGER_HPP
#define SERVER_CALLMANAGER_HPP

#include <memory>
#include <string>
#include "Call.hpp"

namespace babel
{
  class Server;

  class CallManager
  {
   private:
    Server	&_server;

    std::unordered_map<size_t, std::string>	_pendingInvite;
    std::unordered_map<size_t, Call>		_calls;
   public:
    CallManager(Server &server);
    virtual ~CallManager();

    bool invite(size_t idCall, std::string login);
    bool add(size_t idCall, std::string login, std::string ip, unsigned int port);
    bool remove(size_t idCall, std::string login);

    bool isAllowToJoin(size_t idCall, std::string login);
    bool convIsExist(size_t idCall);

    Call create();
    bool finish(size_t idCall);

    const std::unordered_map<size_t, Call> &getCalls() const;
  };
}

#endif //SERVER_CALLMANAGER_HPP
