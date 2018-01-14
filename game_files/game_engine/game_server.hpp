#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include <vector>
#include <iostream>
#include "../tcp/tcp.hpp"
#include "../game_objects/player.hpp"
#include "game_engine.hpp"
#ifdef _WIN32
#include <Winsock2.h>
#include <list>
#include <boost/regex.hpp>
#include <queue>
#include <thread>
#endif /* _WIN32 */

class GameServer {
private:
    static tcp::tcp_server _server;
    static long unsigned int _buffer_length;
    static std::queue<std::string> _queue_requests;
    static std::queue<std::string> _queue_responses;
    std::thread *_thread_requests = nullptr;
    std::thread *_thread_responses = nullptr;
    void process_queue_request();
    void process_queue_response();
    ///void kickPlayer(const std::shared_ptr<tcp::tcp_client>& client);
    static bool _is_running;
    void run();
    GameServer(void);
    ~GameServer(void);
public:
    
    std::string _name="server";
    static GameServer & get();
    void queue_result(std::string result);
    static std::vector<std::shared_ptr<GameEngine>> _engines;
    static std::vector<std::shared_ptr<tcp::tcp_client>> _clients_ptr;
    static void data_collector(const std::shared_ptr<tcp::tcp_client>& client, const tcp::tcp_client::read_result& res);
    void start(const std::string& host, std::uint32_t port);
    std::vector<player_ptr>  getPlayers();

};

#endif // GAME_SERVER_HPP