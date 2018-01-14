#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "../typedefs.hpp"
#include "../tcp/tcp.hpp"
#include <string>
#include <boost/regex.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <queue>
class GameEngine{
private:
    std::vector<player_ptr> _players;
    enum state {WAIT_FOR_PLAYERS=0,WAIT_FOR_MOVE=1,COMPUTE_NEW_STATE=2,GAME_OVER=3};
    state _currentState=WAIT_FOR_PLAYERS;
    state _nxtState;
    std::mutex mtx;
    std::condition_variable cv;
public:
    std::string _name;
    std::queue<std::string> _queue;
    void run();
    void stop();
    std::thread *_thread = nullptr;
    std::thread *_thread2 = nullptr;
    bool _is_running=true;
    void sendCmd(std::string input);
    void start();
    void processInput(std::string input);
    int removePlayer(const std::shared_ptr<tcp::tcp_client>& client);
    void addPlayer( std::string name,const std::shared_ptr<tcp::tcp_client>& _client_ptr);
    std::vector<player_ptr> getPlayers();
    int state();
    GameEngine(std::string _name,std::string _mastername,const std::shared_ptr<tcp::tcp_client>& master);
    ~GameEngine();
protected:
    std::string join(std::string _str);
    std::string gameInit();
    std::string playing(std::string _str);

};


#endif //GAME_ENGINE_HPP