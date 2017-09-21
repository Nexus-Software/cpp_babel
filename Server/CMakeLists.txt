cmake_minimum_required(VERSION 3.7)
project(Server)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(SOURCE_FILES src/main.cpp
        src/Network/Interfaces/INetworkTcpServer.hpp
        src/Network/Interfaces/INetworkTcpServerTunnel.hpp
        src/Log/LogInTerm.cpp
        src/Server.cpp)

add_executable(Server ${SOURCE_FILES})