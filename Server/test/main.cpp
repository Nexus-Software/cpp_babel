/*
** main.cpp for cpp_babel in /home/enguerrand/delivery/cpp_babel/main.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Tue Nov 07 22:41:29 2017 Enguerrand Allamel
** Last update Tue Nov 07 22:41:29 2017 Enguerrand Allamel
*/
#include <gtest/gtest.h>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include "Server.hpp"
#include "Network/Boost/NetworkTcpServerBoost.hpp"


static void run_server()
{
  std::cout.rdbuf(NULL);
  babel::Server	server(42420);
  server.run();
}

int main(int argc, char **argv) {
  boost::thread server(run_server);


boost::thread::sleep(boost::get_system_time() + boost::posix_time::millisec(5000));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
