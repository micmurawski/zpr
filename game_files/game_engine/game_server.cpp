#include "game_server.hpp"
#include "../get_regex_function.hpp"


//Deklaracja pól satycznych
tcp::tcp_server GameServer::_server;
std::vector<std::shared_ptr<tcp::tcp_client>> GameServer::_clients_ptr;
long unsigned int GameServer::_buffer_length=5;
std::queue<std::string> GameServer::_queue_requests;
std::queue<std::string> GameServer::_queue_responses;
std::vector<std::shared_ptr<GameEngine>> GameServer::_engines;
std::mutex GameServer::m_;
bool GameServer::_is_running=true;


//funkcje pomocnicze
bool gameExist(std::string name,const std::vector<std::shared_ptr<GameEngine>>& engines){
  for(std::shared_ptr<GameEngine> engine_ptr : engines){
    if(engine_ptr.get()->_name==name){
      return true;
    }
  }
      return false;
}

std::shared_ptr <GameEngine> GameServer::findGameEngine(std::string name){
  std::vector<std::shared_ptr<GameEngine>>::iterator it0 = find_if(_engines.begin(), _engines.end(),
     [&name] (const std::shared_ptr<GameEngine>& engine) { return engine->_name == name; });
     if(it0!=_engines.end()){
       return *it0;
     }else{
       return nullptr;
     }
}

std::shared_ptr<tcp::tcp_client> GameServer::findTCPClient(std::string host,std::string port){
  std::vector<std::shared_ptr<tcp::tcp_client>>::iterator it1 = 
  find_if(_clients_ptr.begin(), _clients_ptr.end(),
  [&host,&port] (const std::shared_ptr<tcp::tcp_client>& _client_ptr){
  return _client_ptr->get_host() == host && _client_ptr->get_port() == atoi(port.c_str());
         });

    if(it1!=_clients_ptr.end()){
      return *it1;
    }else{
      return nullptr;
    }
}


GameServer::GameServer(){
  std::cout<<"Utworzono server"<<std::endl;
  _thread_requests = new std::thread(&GameServer::process_queue_request, this);
  _thread_responses = new std::thread(&GameServer::process_queue_response, this);
}

GameServer::~GameServer(){
  _is_running=false;
     if (_thread_requests != nullptr) {
            _thread_requests->join();
            delete _thread_requests;
        }
      if (_thread_responses != nullptr) {
            _thread_responses->join();
            delete _thread_responses;
        }
}

GameServer & GameServer::getInstance(){
        lock_guard<mutex> lock(m_);
        static GameServer gameServer;
        return gameServer;
}



std::vector<player_ptr> GameServer::getPlayers(){

}

void GameServer::data_collector(const std::shared_ptr<tcp::tcp_client>& client,const tcp::tcp_client::read_result& res){
  if (res.success) {
    std::cout << "Otrzymano dane: " <<std::endl;
    std::string str = std::string(res.buffer.begin(), res.buffer.end());
    //std::cout<< "Klient:"<< client->get_host() << "Wysyła: " <<str<<std::endl;
    //Wyrażenie regularne sprawdzające długosc kolejnego buffora <length=?/>
    if(strspn(str.c_str(), "0123456789") == str.size() ){
      //std::cout << "Otrzymano długość komendy"<<std::endl;
      int i = stoi(str);
      GameServer::_buffer_length = strtoul (std::to_string(i).c_str(), NULL, 0);
    }else{
      std::cout << "Otrzymano komende"<<std::endl;
      str = "<ip>"+client->get_host()+"</ip><port>"+std::to_string(client->get_port())+"</port>"+str;
      GameServer::_queue_requests.push(str);
      //przygotowanie buffora na przyjecie kolejnej dlugosci
      GameServer::_buffer_length = 5;
    }
    client->async_read({_buffer_length, std::bind(&data_collector, client, std::placeholders::_1)});
  }
  else {

    std::cout << "Klient opuścił gre"<< std::endl;
    //Usuwanie gracza
    //Usuwanie instancji gry
    _engines.erase(
    std::remove_if(
    _engines.begin(),
    _engines.end(),
    [&client](const std::shared_ptr<GameEngine> engine_ptr){ return engine_ptr.get()->removePlayer(client)==0; }
    ),
    _engines.end());
    _clients_ptr.erase(std::remove(_clients_ptr.begin(), _clients_ptr.end(), client), _clients_ptr.end());
    client->disconnect();
    
  }
};

void GameServer::start(const std::string& host="127.0.0.1", std::uint32_t port=3002){
    _server.start(host, port, [&](const std::shared_ptr<tcp::tcp_client>& client) -> bool {
    std::cout << "Nowy klient dołączył do serwera" <<client->get_host()<< std::endl;
    GameServer::_clients_ptr.push_back(client);
    std::string lista = getLobby();
    std::vector<char> listaGier(lista.begin(), lista.end());
    client->async_write({listaGier, nullptr});
    client->async_read({_buffer_length, std::bind(&data_collector, client, std::placeholders::_1)});
    return true;
  });
}

void GameServer::process_queue_request(){
while(_is_running){
   while(!_queue_requests.empty()){
//przetwarzanie danych z kolejki otrzymanych danych
std::string request = _queue_requests.front();
_queue_requests.pop();
std::string join = getJoin(request);
std::string create = getCreate(request);
//odczytanie "adresata"
std::string host = getIp(request);
std::string port = getPort(request);
std::string name = getName(request);
std::cout<<host<<port<<name<<"join="<<join<<"create="<<create<<std::endl;
if(join!=""){
  std::cout<<"JOIN!"<<std::endl;
  std::shared_ptr<GameEngine> engine_ptr = findGameEngine(join);
  std::shared_ptr<tcp::tcp_client> client_ptr = findTCPClient(host,port);
  // sprawdzenie czy gra istnieje
  if(engine_ptr==nullptr){
    std::cout<<"engine nullptr!"<<std::endl;
    //gra nie istnieje byebye
    pushToQueueResponse("<ip>"+host+"</ip><port>"+port+
    "</port><msg>Gra o podanej nazwie istnieje. Wybierz innną nazwę</msg>");
  }else if(engine_ptr!=nullptr){
    std::cout<<"DODAWANIE"<<std::endl;
    //gra istnieje dołączanie gracza
      pushToQueueResponse("<ip>"+host+"</ip><port>"+port+"</port><msg>Dołączonono do gry</msg>");
      engine_ptr.get()->addPlayer(name,client_ptr);
      engine_ptr.get()->_queue.push("HANDSHAKE");
   // 
  }
}
if(create!=""){
  std::cout<<"create!"<<std::endl;
  std::shared_ptr<GameEngine> engine_ptr = findGameEngine(create);
  std::shared_ptr<tcp::tcp_client> client_ptr = findTCPClient(host,port);
  //sprawdzenie czy gra istnieje
  if(engine_ptr!=nullptr){
    //gra istnieje byebye
    std::cout<<"Gra nie istnieje"<<std::endl;
    pushToQueueResponse("<ip>"+host+"</ip><port>"+port+"</port><msg>Gra o podanej nazwie nie istnieje. Wybierz innną nazwę</msg>"); 
  }else{
    std::cout<<"tworzenie nowej gry!"<<std::endl;
    //Utworzenie nnowej gry
    std::shared_ptr<tcp::tcp_client> client_ptr = findTCPClient(host,port);
    std::shared_ptr<GameEngine> engine_ptr = findGameEngine(create);
    _engines.push_back(std::make_shared<GameEngine>(create,name,client_ptr));
    _engines.back()->_queue.push("HANDSHAKE");
    pushToQueueResponse("<ip>"+host+"</ip><port>"+port+"</port><msg>Utworzono grę</msg>");
    }
}

   }
   }
}
void GameServer::pushToQueueResponse(std::string str){
  int digits = std::to_string(str.size()).size();
  std::string tmp = std::string( 5-digits, '0').append(std::to_string(str.size()));
  _queue_responses.push(tmp+str);
}

void GameServer::process_queue_response(){
  //przesyłanie odpowiedzi do klientów
  while(_is_running){
    while(!_queue_responses.empty()){
        std::string response = _queue_responses.front();
        _queue_responses.pop();
        std::cout<<"Wysyłanie odpowiedzi: "<<response<<std::endl;
        std::string host = getIp(response);
        std::string port = getPort(response);
        std::shared_ptr<tcp::tcp_client> client_ptr = findTCPClient(host,port);
        for(std::shared_ptr<tcp::tcp_client> client_ptr : _clients_ptr) std::cout<<client_ptr.get()->get_host()<<client_ptr.get()->get_port()<<std::endl;
        if(client_ptr !=nullptr){
          std::cout<<"Do klienta"<<client_ptr->get_host()<<std::endl;
          std::vector<char> sendable(response.begin(), response.end());
          client_ptr->async_write({sendable, nullptr});
        }else{
          std::cout<<"nie znaleziono klienta"<<std::endl;
        }

    }
  }
}


std::string GameServer::getLobby(){
  std::string result="NAZWA GRY\n";
  if(_engines.size()>0)for(std::shared_ptr<GameEngine> engine_ptr : _engines) result+=engine_ptr.get()->_name+"\n";
  return "";
}



