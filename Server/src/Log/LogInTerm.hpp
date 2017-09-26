/*
** LogInTerm.hpp for Server in /home/enguerrand/delivery/Server/LogInTerm.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 10:49:50 2017 Enguerrand Allamel
** Last update jeu. sept. 21 10:49:50 2017 Enguerrand Allamel
*/

#ifndef SERVER_LOGINTERM_HPP
#define SERVER_LOGINTERM_HPP

#include <memory>
#include <iostream>
#include <unordered_map>

namespace babel {
  class LogInTerm
  {
   public:
    enum class LevelLog {
      DEFAULT = 0,
      INFO = 1,
      SUCCESS = 2,
      WARNING = 3,
      ERROR = 4,
      FATAL_ERROR = 5
    };
   private:
    std::unordered_map<LevelLog, std::function<void(const std::string)>> _printTypeFunc;
   public:
    LogInTerm();
    ~LogInTerm();

    void print(const std::string & msg, const LevelLog level = LevelLog::DEFAULT) const;
  };
}

#endif //SERVER_LOGINTERM_HPP
