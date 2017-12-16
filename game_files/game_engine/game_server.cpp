#include "game_server.hpp"

tcp::tcp_server GameServer::_server;
std::vector<std::shared_ptr<tcp::tcp_client>> GameServer::_clients_ptr;

GameServer::GameServer(){
  
}

GameServer & GameServer::get(){
        static GameServer gameServer;
        return gameServer;
}

int GameServer::getClients(tcp::tcp_server *_server){
  return _server->get_clients().size();
}

void GameServer::state_processor(const std::shared_ptr<tcp::tcp_client>& client,const tcp::tcp_client::read_result& res){
  if (res.success) {
    std::cout << "Otrzymano dane: " <<std::endl;
    GameEngine::get().sendCmd(std::string(res.buffer.begin(), res.buffer.end()),client->get_host());
    std::cout<<"GAME_STATE: "<<GameEngine::get().state()<<std::endl;
    //_clients_ptr[0]->async_write({{'g','','i'}, nullptr});
    client->async_read({1024, std::bind(&state_processor, client, std::placeholders::_1)});
  }
  else {

    std::cout << "Klient opuścił gre"<< std::endl;
    std::cout<<GameEngine::get().getPlayers()<<std::endl;
    GameEngine::get().removePlayer(client);
    _clients_ptr.erase(std::remove(_clients_ptr.begin(), _clients_ptr.end(), client), _clients_ptr.end());
    std::cout<<"ilosc obecznych graczy: "<<GameEngine::get().getPlayers()<<std::endl;
    client->disconnect();
    
  }
};

void GameServer::start(const std::string& host="127.0.0.1", std::uint32_t port=3002){
    _server.start(host, port, [&](const std::shared_ptr<tcp::tcp_client>& client) -> bool {
    std::cout << "Nowy klient dołączył do gry " <<client->get_host()<< std::endl;
    GameServer::_clients_ptr.push_back(client);
    for(std::shared_ptr<tcp::tcp_client> i : _clients_ptr){
      std::cout<<i->get_host()<<std::endl;
    }
    client->async_read({1024, std::bind(&state_processor, client, std::placeholders::_1)});
    return true;
  });
}

