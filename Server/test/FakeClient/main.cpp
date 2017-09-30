/*
** main.cpp for Server in /home/enguerrand/delivery/Server/main.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  sam. sept. 23 15:36:31 2017 Enguerrand Allamel
** Last update sam. sept. 23 15:36:31 2017 Enguerrand Allamel
*/

#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

#pragma pack(push, 1)
struct network_data {
  std::uint32_t proto_code;
  std::uint32_t proto_size;
  std::array<char, 2048> body;
};
struct CLIENT_CONTACT_STRUCT
{
  char		login[32];
  std::uint8_t	isOnline;
};
struct NetworkDataSCContactList
{
  CLIENT_CONTACT_STRUCT	contacts[50];
};
#pragma pack(pop)

int main()
{
  {
    boost::asio::io_service ios;
    tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 42420);
    tcp::socket socket(ios);
    socket.connect(endpoint);

    network_data data = {0};
    {
      data = {0};
      data.proto_code = 1;
      data.proto_size = 64;
      std::memcpy(data.body.data(), std::string("michel").c_str(), 32);
      std::memcpy(data.body.data() + 32, std::string("er").c_str(), 32);
      socket.write_some(boost::asio::buffer(&data, sizeof(data)));
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));
      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
    }

    {
      data = {0};
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));

      NetworkDataSCContactList networkDataSCContactList;

      std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList),
		  reinterpret_cast<char *>(&networkDataSCContactList));

      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
      std::cout << "Contact :" << networkDataSCContactList.contacts[0].login << std::endl;
    }
  }
  	std::cout << "-----------------------------------------------------" << std::endl;
  {
    boost::asio::io_service ios;
    tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 42420);
    tcp::socket socket(ios);
    socket.connect(endpoint);

    network_data data = {0};
    {
      data = {0};
      data.proto_code = 1;
      data.proto_size = 64;
      std::memcpy(data.body.data(), std::string("ty").c_str(), 32);
      std::memcpy(data.body.data() + 32, std::string("er").c_str(), 32);
      socket.write_some(boost::asio::buffer(&data, sizeof(data)));
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));
      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
    }

    {
      data = {0};
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));

      NetworkDataSCContactList networkDataSCContactList;

      std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList),
		  reinterpret_cast<char *>(&networkDataSCContactList));

      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
      std::cout << "Contact :" << networkDataSCContactList.contacts[0].login << std::endl;
    }

    {
      data = {0};
      data.proto_code = 4;
      data.proto_size = 32;
      std::memcpy(data.body.data(), std::string("michel").c_str(), sizeof("michel"));
      socket.write_some(boost::asio::buffer(&data, sizeof(data)));
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));
      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
    }

    {
      data = {0};
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));

      NetworkDataSCContactList networkDataSCContactList;

      std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList), reinterpret_cast<char *>(&networkDataSCContactList));

      std::cout << "Received code: " << data.proto_code << std::endl;
      std::cout << "Received size: " << data.proto_size << std::endl;
      std::cout << "Contact :" << networkDataSCContactList.contacts[0].login << std::endl;
    }
  }

  return 0;
}