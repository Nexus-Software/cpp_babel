/*
** server_protocol.cpp for cpp_babel in /home/enguerrand/delivery/cpp_babel/server_protocol.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue Nov 07 22:00:02 2017 Enguerrand Allamel
** Last update Tue Nov 07 22:00:02 2017 Enguerrand Allamel
*/

#include <gtest/gtest.h>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

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

TEST(ServerProtocol, InitLogin) {
boost::asio::io_service ios;
tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 42420);
tcp::socket socket(ios);
socket.connect(endpoint);
}

TEST(ServerProtocol, SignUp) {
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

EXPECT_EQ(data.proto_code, 45);
EXPECT_EQ(data.proto_size, 0);
}
}

TEST(ServerProtocol, Login) {
	boost::asio::io_service ios;
    tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 42420);
    tcp::socket socket(ios);
    socket.connect(endpoint);

    network_data data = {0};
    {
      data = {0};
      data.proto_code = 2;
      data.proto_size = 64;
      std::memcpy(data.body.data(), std::string("michel").c_str(), 32);
      std::memcpy(data.body.data() + 32, std::string("er").c_str(), 32);
      socket.write_some(boost::asio::buffer(&data, sizeof(data)));
      socket.read_some(boost::asio::buffer(&data, sizeof(data)));
      EXPECT_EQ(data.proto_code, 44);
      EXPECT_EQ(data.proto_size, 0);
    }
}

TEST(ServerProtocol, AddContact) {
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
}

{
data = {0};
socket.read_some(boost::asio::buffer(&data, sizeof(data)));

NetworkDataSCContactList networkDataSCContactList;

std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList),
reinterpret_cast<char *>(&networkDataSCContactList));
}

{
data = {0};
data.proto_code = 4;
data.proto_size = 32;
std::memcpy(data.body.data(), std::string("michel").c_str(), sizeof("michel"));
socket.write_some(boost::asio::buffer(&data, sizeof(data)));
socket.read_some(boost::asio::buffer(&data, sizeof(data)));
EXPECT_EQ(data.proto_code, 47);
EXPECT_EQ(data.proto_size, 0);
}

{
data = {0};
socket.read_some(boost::asio::buffer(&data, sizeof(data)));

NetworkDataSCContactList networkDataSCContactList;

std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList), reinterpret_cast<char *>(&networkDataSCContactList));

EXPECT_EQ(data.proto_code, 6);
EXPECT_EQ(data.proto_size, 1800);
ASSERT_STREQ(networkDataSCContactList.contacts[0].login, "michel");
}
}

TEST(ServerProtocol, RemoveContact) {
boost::asio::io_service ios;
tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 42420);
tcp::socket socket(ios);
socket.connect(endpoint);

network_data data = {0};
{
data = {0};
data.proto_code = 2;
data.proto_size = 64;
std::memcpy(data.body.data(), std::string("ty").c_str(), 32);
std::memcpy(data.body.data() + 32, std::string("er").c_str(), 32);
socket.write_some(boost::asio::buffer(&data, sizeof(data)));
socket.read_some(boost::asio::buffer(&data, sizeof(data)));
}

{
data = {0};
socket.read_some(boost::asio::buffer(&data, sizeof(data)));

NetworkDataSCContactList networkDataSCContactList;

std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList),
reinterpret_cast<char *>(&networkDataSCContactList));
}

{
data = {0};
data.proto_code = 3;
data.proto_size = 32;
std::memcpy(data.body.data(), std::string("michel").c_str(), sizeof("michel"));
socket.write_some(boost::asio::buffer(&data, sizeof(data)));
socket.read_some(boost::asio::buffer(&data, sizeof(data)));
EXPECT_EQ(data.proto_code, 46);
EXPECT_EQ(data.proto_size, 0);
}

{
data = {0};
socket.read_some(boost::asio::buffer(&data, sizeof(data)));

NetworkDataSCContactList networkDataSCContactList;

std::copy_n(reinterpret_cast<const char *>(&data.body), sizeof(NetworkDataSCContactList), reinterpret_cast<char *>(&networkDataSCContactList));

EXPECT_EQ(data.proto_code, 6);
EXPECT_EQ(data.proto_size, 1800);
ASSERT_STREQ(networkDataSCContactList.contacts[0].login, "");
}
}