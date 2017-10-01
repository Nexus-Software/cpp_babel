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
#include <functional>

namespace babel {
  struct EnumClassHash
  {
    template <typename T>
    std::size_t operator()(T t) const
    {
      return static_cast<std::size_t>(t);
    }
  };

  class LogInTerm
  {
   public:
    enum class LevelLog {
      DEFAULT 	= 0,
      INFO 	= 1,
      SUCCESS,
      WARNING,
      ERROR,
      FATAL_ERROR
    };

   private:
    std::unordered_map<LevelLog, std::function<void(const std::string)>, babel::EnumClassHash> _printTypeFunc;
   public:
    LogInTerm();
    ~LogInTerm();

    void print(const std::string & msg, const LevelLog level = LevelLog::DEFAULT) const;
  };
}

#endif //SERVER_LOGINTERM_HPP
