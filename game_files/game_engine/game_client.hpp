#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP
#include "../tcp/tcp.hpp"
#include <string>
#include <condition_variable>
#include <iostream>
#include<vector>
#include <mutex>
#include <signal.h>
#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */

class GameClient{

public:
static tcp::tcp_client _client;
static std::string _name;

static void read(tcp::tcp_client& client, const tcp::tcp_client::read_result& res);
static void connect(const std::string& host, std::uint32_t port);
static void sendCmd(std::string cmd);
static void join();

};


#endif //GAME_CLIENT_HPP