#include "game_client.hpp"
#include "../get_regex_function.hpp"

//Deklaracja pól statycznych
tcp::tcp_client GameClient::_client;
std::string GameClient::_name="noname";
std::queue<std::string> GameClient::_queue;
std::mutex m_;
unsigned int GameClient::_buffer_length=5;

void GameClient::processQueue(){
  while(_is_running){
    while(!_queue.empty()){
        std::string response = _queue.front();
        _queue.pop();
        std::cout<<"przetwarzanie ..."<<response.size()<<std::endl;
        std::cout<<response<<std::endl;
        //Zwalnianie blokady w trakcie dołączenia przeciwnika
        if(wait_){
          std::string start = getRegex(response,"(?<=<start>)(.*)(?=</start>)");
          if(start=="1"){
          std::string gameStateString = getRegex(response,"(?<=<game_state>)(.*)(?=</game_state>)");
          std::cout<<"załadowano poczatkowy game state"<<std::endl;
          std::cout<<gameStateString<<std::endl;
           gameState_.loadFromString(gameStateString);
           //gameState_ptr_ = std::make_shared()
           gameState_ptr_.get()->loadFromString(gameStateString);
           std::cout<<"wypisywanie"<<std::endl;
           for(player_ptr ptr : gameState_.players_) std::cout<<ptr.get()->name_<<std::endl;
           std::cout<<"ok"<<std::endl;
             wait_=false;
          }
          
          }
        std::string gameStateString = getRegex(response,"(?<=<game_state>)(.*)(?=</game_state>)");
        if(gameStateString!=""){
          std::cout<<"załadowano nowy game state"<<std::endl;
          gameState_ptr_.get()->loadFromString(gameStateString);
        }
    }
  }
}

GameClient::GameClient(){
  //Uruchomienie wątku przetwarzania kolejki, zabezpieczyć mutexem
  std::cout<<"Utworzono klienta gry"<<std::endl;
  _thread= new std::thread(&GameClient::processQueue, this);
  gameState_ptr_ = std::make_shared<GameState>();
}

GameClient::~GameClient(){
  _is_running=false;
     if (_thread!= nullptr) {
            _thread->join();
            delete _thread;
        }

}

void GameClient::read(tcp::tcp_client& client, const tcp::tcp_client::read_result& res) {
  if (res.success) {
      std::string str = std::string(res.buffer.begin(), res.buffer.end());
      std::cout<<"ODCZYTANO: "<<str<<std::endl;
      if(strspn(str.c_str(), "0123456789") == str.size() ){
      int i = stoi(str);
      GameClient::_buffer_length = strtoul (std::to_string(i).c_str(), NULL, 0);
      std::cout << "Otrzymano długość komendy: "<<GameClient::_buffer_length<<std::endl;
    }else{
      _queue.push(std::string(res.buffer.begin(), res.buffer.end()));
      GameClient::_buffer_length = 5;
    }
       std::cout<<std::string(res.buffer.begin(), res.buffer.end())<<std::endl;
       _queue.push(std::string(res.buffer.begin(), res.buffer.end()));
       client.async_read({_buffer_length, std::bind(&read,std::ref(client), std::placeholders::_1)});
    }
    else {
      std::cout << "Klient został odłączony" << std::endl;
      client.disconnect();
    }
    
}


GameClient & GameClient::getInstance(){
        std::lock_guard<std::mutex> lock(m_);
        static GameClient gameClient;
        return gameClient;
}

void GameClient::connect(const std::string& host="127.0.0.1", std::uint32_t port=3002){
  try{
      _client.connect(host,port);
      std::cout<<_client.get_host()<<":"<<_client.get_port() << std::endl;
    }catch(tcp::tcp_error error){
      std::cout<<"nie udało się połączyć z serverem TCP"<<error.what()<<std::endl;
    }
    _client.async_read({5, std::bind(&read, std::ref(_client), std::placeholders::_1)});
}

void GameClient::sendCmd(std::string cmd){
  std::string preamble = "<name>"+_name+"</name>";
  std::string tmp = preamble+"<cmd>"+cmd+"</cmd>";
  int digits = std::to_string(tmp.size()).size();
  tmp = std::string( 5-digits, '0').append(std::to_string(tmp.size()))+tmp;
  std::cout<<"Wysyłanie.. "<<tmp<<std::endl;
  std::vector<char> sendable(tmp.begin(), tmp.end());
  _client.async_write({sendable, nullptr});
}

void GameClient::join(){
  std::string cmd = "<join>"+_name+"</join>";
  cmd = "0"+std::to_string(cmd.length())+cmd;
  sendCmd(cmd);
}

