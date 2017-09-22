/*
** NetworkException.hpp for Server in /home/enguerrand/delivery/Server/NetworkException.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  ven. sept. 22 20:03:08 2017 Enguerrand Allamel
** Last update ven. sept. 22 20:03:08 2017 Enguerrand Allamel
*/

#ifndef SERVER_NETWORKEXCEPTION_HPP
#define SERVER_NETWORKEXCEPTION_HPP

#include <exception>
#include <string>

namespace babel {
  class NetworkException : public std::exception
  {
   protected:
    std::string _msg;
   public:

    explicit NetworkException(const char* message):			_msg(message)	{}
    explicit NetworkException (const std::string& message):	_msg(message)	{}

    virtual ~NetworkException () throw () {}

    virtual const char* what() const throw () { return this->_msg.c_str(); }
  };
}

#endif //SERVER_NETWORKEXCEPTION_HPP
