/*
** Server.hpp for Server in /home/enguerrand/delivery/Server/Server.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mer. sept. 20 18:51:53 2017 Enguerrand Allamel
** Last update mer. sept. 20 18:51:53 2017 Enguerrand Allamel
*/

#ifndef SERVER_SERVER_HPP
#define SERVER_SERVER_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include "Error/Errors.hpp"
#include "Account/AccountManager.hpp"
#include "BabelNetworkMacro.hpp"
#include "Network/Interfaces/INetworkManager.hpp"
#include "Log/LogInTerm.hpp"
#include "Cmd/HandleCmd.hpp"

namespace babel {
  class Server {
   protected:
    unsigned int								_port;
    std::shared_ptr<INetworkManager>						_networkManager;
    LogInTerm									_logInTerm;
    HandleCmd									_handleCmd;
    AccountManager								_accountManager;
   public:
    Server(unsigned int port = 4242);
    ~Server();

    void run();

    const LogInTerm & getLogInTerm() const;

    HandleCmd & getHandleCmd();
    AccountManager & getAccountManager();

    const AccountManager & getAccountManager() const;

    std::shared_ptr<babel::INetworkManager> getNetworkManager();
  };
}

#endif //SERVER_SERVER_HPP
