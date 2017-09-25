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

int main()
{
  boost::asio::io_service ios;
  tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4546);
  tcp::socket socket(ios);

  socket.connect(endpoint);

  std::uint32_t i = 2;
  socket.write_some(boost::asio::buffer(&i, 4));
  i = 64;
  socket.write_some(boost::asio::buffer(&i, 4));
  socket.write_some(boost::asio::buffer("Admin\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 32));
  socket.write_some(boost::asio::buffer("Passs\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 32));
  socket.read_some(boost::asio::buffer(&i, 4));
  std::cout << "Received code: " << i << std::endl;
  socket.read_some(boost::asio::buffer(&i, 4));
  std::cout << "Received size: " << i << std::endl;
  return 0;
}