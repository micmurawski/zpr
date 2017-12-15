#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP
#include "../tcp/tcp.hpp"
#include "game_engine.hpp"
#include <iostream>
#include "../game_objects/player.hpp"
#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */

class GameServer {
private:
    static tcp::tcp_server _server;
    GameServer(void);
public:
    std::string _name;
    static GameServer & get();
    static std::vector<std::shared_ptr<tcp::tcp_client>> _clients_ptr;
    static void state_processor(const std::shared_ptr<tcp::tcp_client>& client, const tcp::tcp_client::read_result& res);
    static void serverDataFlow(const std::shared_ptr<tcp::tcp_client>& client);
    void start(const std::string& host, std::uint32_t port);
    static int getClients(tcp::tcp_server *_server);

};

#endif // GAME_SERVER_HPP