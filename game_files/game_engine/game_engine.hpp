
#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "../typedefs.hpp"
#include "../tcp/tcp.hpp"
#include "game_server.hpp"
#include <string>
#include <boost/regex.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <queue>
class GameEngine{
private:
    static std::vector<player_ptr> _players;
    std::queue<std::string> _queue;
    enum state {WAIT_FOR_PLAYERS=0,GAME_INIT=1,PLAYING=2,GAME_OVER=3};
    state _currentState;
    state _nxtState;
    std::thread *_thread = nullptr;
    GameEngine();
    bool _is_running=true;
public:
    static GameEngine & get();
    void run();
    void sendCmd(std::string input,std::string host);
    void start();
    void processInput(std::string input);
    void removePlayer(std::shared_ptr<tcp::tcp_client> client);
    int getPlayers();
    int state();
    ~GameEngine();
protected:
    std::string join(std::string _str);
    std::string gameInit();
    std::string playing(std::string _str);

};


#endif //GAME_ENGINE_HPP