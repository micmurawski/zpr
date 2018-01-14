#include "game_client.hpp"

tcp::tcp_client GameClient::_client;
std::string GameClient::_name="noname";

void GameClient::read(tcp::tcp_client& client, const tcp::tcp_client::read_result& res) {
  if (res.success) {
       std::cout<<std::string(res.buffer.begin(), res.buffer.end())<<std::endl;
       client.async_read({1024, std::bind(&read,std::ref(client), std::placeholders::_1)});
    }
    else {
      std::cout << "Klient został odłączony" << std::endl;
      client.disconnect();
    }
}

GameClient::~GameClient(){
}

void GameClient::connect(const std::string& host="127.0.0.1", std::uint32_t port=3002){
  try{
      _client.connect(host,port);
      std::cout<<_client.get_host()<<":"<<_client.get_port() << std::endl;
    }catch(tcp::tcp_error error){
      std::cout<<"nie udało się połączyć z serverem TCP"<<error.what()<<std::endl;
    }
    _client.async_read({1024, std::bind(&read, std::ref(_client), std::placeholders::_1)});
}

void GameClient::sendCmd(std::string cmd){
  std::string preamble = "<name>"+_name+"</name>";
  std::string tmp = preamble+"<cmd>"+cmd+"</cmd>";
  int digits = ceil(8*sizeof(tmp.length()) * log10(2)/10);
  tmp = std::to_string(tmp.length())+tmp;
  std::cout<<digits<<std::endl;
  if(3-digits>0){
    for(int i=0;i<3-digits;i++){
      tmp="0"+tmp;
    }
  }
  std::cout<<"Wysyłanie.. "<<tmp<<std::endl;
  std::vector<char> sendable(tmp.begin(), tmp.end());
  _client.async_write({sendable, nullptr});
}

void GameClient::join(){
  std::string cmd = "<join>"+_name+"</join>";
  cmd = "0"+std::to_string(cmd.length())+cmd;
  sendCmd(cmd);
}

