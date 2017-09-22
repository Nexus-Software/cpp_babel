/*
** LogInTerm.cpp for Server in /home/enguerrand/delivery/Server/LogInTerm.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  jeu. sept. 21 10:49:50 2017 Enguerrand Allamel
** Last update jeu. sept. 21 10:49:50 2017 Enguerrand Allamel
*/

#include "LogInTerm.hpp"

babel::LogInTerm::LogInTerm()
{
}

babel::LogInTerm::~LogInTerm()
{
}

void babel::LogInTerm::print(const std::string & msg, const LevelLog level) const
{
  if (level == LevelLog::INFO)
    std::cout << "[INFO]: ";
  else if (level == LevelLog::SUCCESS)
    std::cout << "[SUCCESS]: ";
  else if (level == LevelLog::WARNING)
    std::cout << "[WARNING]: ";
  else if (level == LevelLog::ERROR)
    std::cout << "[ERROR]: ";
  else if (level == LevelLog::FATAL_ERROR)
    std::cout << "[FATAL_ERROR] [SERVER HALT NOW]: ";
  std::cout << msg << std::endl;
}