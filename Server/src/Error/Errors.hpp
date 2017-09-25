/*
** Errors.hpp for Server in /home/enguerrand/delivery/Server/Errors.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  lun. sept. 25 14:37:17 2017 Enguerrand Allamel
** Last update lun. sept. 25 14:37:17 2017 Enguerrand Allamel
*/

#ifndef SERVER_ERRORS_HPP
#define SERVER_ERRORS_HPP

#include <exception>
#include <string>

namespace babel {
  class AccountManagerException : public std::exception
  {
   protected:
    std::string _msg;
   public:

    explicit AccountManagerException(const char* message): _msg(message) {}
    explicit AccountManagerException (const std::string& message): _msg(message) {}

    virtual ~AccountManagerException () throw () {}

    virtual const char* what() const throw () { return this->_msg.c_str(); }
  };
}

#endif //SERVER_ERRORS_HPP
