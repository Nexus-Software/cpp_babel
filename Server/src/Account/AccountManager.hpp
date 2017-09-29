/*
** AccountManager.hpp for Server in /home/enguerrand/delivery/Server/AccountManager.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  dim. sept. 24 23:44:12 2017 Enguerrand Allamel
** Last update dim. sept. 24 23:44:12 2017 Enguerrand Allamel
*/

#ifndef SERVER_ACCOUNTMANAGER_HPP
#define SERVER_ACCOUNTMANAGER_HPP

#include <string>
#include <unordered_map>
#include "Account.hpp"

namespace babel
{
  class Server;

  class AccountManager
  {
   protected:
    Server	&_server;

    std::unordered_map<std::string, Account>	_accountList;
   public:
    AccountManager(Server &server);
    virtual ~AccountManager();

    bool add(std::string login, std::string password);
    bool remove(std::string login);

    Account getAccountByLogin(const std::string login);
    const Account getAccountByLogin(const std::string login) const;

    const std::unordered_map<std::string, Account> &getAccountList() const;

    bool addContact(const std::string & login_req, const std::string & login);
    bool removeContact(const std::string & login_req, const std::string & login);

    void sendContactList(size_t tunnelId, std::string login);
  };
}

#endif //SERVER_ACCOUNTMANAGER_HPP
