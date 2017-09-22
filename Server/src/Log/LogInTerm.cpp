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
  this->_printTypeFunc =
	  {
		  {LevelLog::INFO,        [&](const std::string) { std::cout << "[INFO]: "; }},
		  {LevelLog::SUCCESS,     [&](const std::string) { std::cout << "[SUCCESS]: "; }},
		  {LevelLog::WARNING,     [&](const std::string) { std::cout << "[WARNING]: "; }},
		  {LevelLog::ERROR,       [&](const std::string) { std::cout << "[ERROR]: "; }},
		  {LevelLog::FATAL_ERROR, [&](const std::string) { std::cout << "[FATAL_ERROR] [SERVER HALT NOW]: "; }}};
}

babel::LogInTerm::~LogInTerm()
{
}

void babel::LogInTerm::print(const std::string &msg, const LevelLog level) const
{
  if (this->_printTypeFunc.find(level) != this->_printTypeFunc.end())
    this->_printTypeFunc.find(level)->second(msg);
  std::cout << msg << std::endl;
}