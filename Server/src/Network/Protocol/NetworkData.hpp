/*
** NetworkData.hpp for Server in /home/enguerrand/delivery/Server/NetworkData.hpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  mar. sept. 26 23:14:37 2017 Enguerrand Allamel
** Last update mar. sept. 26 23:14:37 2017 Enguerrand Allamel
*/

#ifndef SERVER_NETWORKDATA_HPP
#define SERVER_NETWORKDATA_HPP

#include <array>

namespace babel
{
  struct NetworkData
  {
    NetworkData() {};
    NetworkData(std::uint32_t code, std::uint32_t size, std::array<char, 2048> data): code(code), size(size), data(data) {};
    std::uint32_t 		code;
    std::uint32_t 		size;
    std::array<char, 2048> 	data;
  };

  struct CLIENT_CONTACT_STRUCT
  {
    char		login[32];
    std::uint32_t	isOnline;
  };

  struct CLIENT_CALL_STRUCT
  {
    char		login[32];
    char 		ip[16];
    std::uint32_t	port;
  };

  struct NetworkDataCSJoin
  {
    std::uint32_t 	idCall;
    unsigned int	port;
  };

  struct NetworkDataSCJoin
  {
    std::uint32_t 	idCall;
    CLIENT_CALL_STRUCT	client;
  };

  struct NetworkDataCSJoinSuccess
  {
    std::uint32_t 	idCall;
    CLIENT_CALL_STRUCT	client[8];
  };

  struct NetworkDataCSInvite
  {
    std::uint32_t 	idCall;
    char 		loginInvite[32];
  };

  struct NetworkDataSCContactList
  {
    CLIENT_CONTACT_STRUCT	contacts[50];
  };
  struct NetworkDataSCInvite
  {
    std::uint32_t 	idCall;
    char 		clientInConv[8][32];
    char		loginHasInvite[32];
  };
}

#endif //SERVER_NETWORKDATA_HPP
