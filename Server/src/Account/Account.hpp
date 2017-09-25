/*
** Account.hpp for Server in /home/enguerrand/delivery/Server/Account.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 23:44:28 2017 Enguerrand Allamel
** Last update dim. sept. 24 23:44:28 2017 Enguerrand Allamel
*/

#ifndef SERVER_ACCOUNT_HPP
#define SERVER_ACCOUNT_HPP

#include <string>
#include <algorithm>
#include <vector>

namespace babel
{
  class Account
  {
   protected:
    std::string			_login;
    std::string			_password;
    bool 			_isOnline;
    std::vector<std::string>	_contactList;
   public:
    Account(std::string login, std::string password);
    virtual ~Account();

    const std::string 			&getLogin() const;
    const std::string 			&getPassword() const;
    bool 				getIsOnline() const;
    const std::vector<std::string> 	&getContactList() const;

    void setPassword(const std::string &password);
    void setIsOnline(bool isOnline);

    bool addContact(const std::string & login);
    bool removeContact(const std::string & login);
  };
}

#endif //SERVER_ACCOUNT_HPP
