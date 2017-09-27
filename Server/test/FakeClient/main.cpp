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
#pragma pack(pop)

int main()
{
  boost::asio::io_service ios;
  tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4546);
  tcp::socket socket(ios);
  socket.connect(endpoint);

  network_data data = {0};
  data.proto_code = 1;
  data.proto_size = 64;
  std::memcpy(data.body.data(), "Admin\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 32);
  std::memcpy(data.body.data() + 32, "Admin\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 32);
  socket.write_some(boost::asio::buffer(&data, sizeof(data)));
  socket.read_some(boost::asio::buffer(&data, sizeof(data)));
  std::cout << "Received code: " << data.proto_code << std::endl;
  std::cout << "Received size: " << data.proto_size << std::endl;
  while (1);
  return 0;
}