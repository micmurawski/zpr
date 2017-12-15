#include "game_client.hpp"

tcp::tcp_client GameClient::_client;
std::string GameClient::_name;

void GameClient::read(tcp::tcp_client& client, const tcp::tcp_client::read_result& res) {
  if (res.success) {
    //odczytwanie stanu gry
    //res.buffer
       client.async_read({1024, std::bind(&read,std::ref(client), std::placeholders::_1)});
    }
    else {
      std::cout << "Klient został odłączony" << std::endl;
      client.disconnect();
    }
}

void GameClient::connect(const std::string& host="127.0.0.1", std::uint32_t port=3002){
  try{
      _client.connect(host,port);
      std::cout<<_client.get_host() <<_client.get_port() << std::endl;
    }catch(tcp::tcp_error error){
      std::cout<<"nie udało się połączyć z serverem TCP"<<error.what()<<std::endl;
    }
    _client.async_read({1024, std::bind(&read, std::ref(_client), std::placeholders::_1)});
}

void GameClient::sendCmd(std::string cmd){
  std::vector<char> sendable(cmd.begin(), cmd.end());
  _client.async_write({sendable, nullptr});
}

void GameClient::join(){
  std::string cmd = "<join>"+_name+"</join>";
  std::vector<char> sendable(cmd.begin(), cmd.end());
  _client.async_write({sendable, nullptr});
}

