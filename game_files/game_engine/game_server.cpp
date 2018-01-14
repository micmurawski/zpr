#include "game_server.hpp"

tcp::tcp_server GameServer::_server;
std::vector<std::shared_ptr<tcp::tcp_client>> GameServer::_clients_ptr;
long unsigned int GameServer::_buffer_length=3;
std::queue<std::string> GameServer::_queue_requests;
std::queue<std::string> GameServer::_queue_responses;
std::vector<std::shared_ptr<GameEngine>> GameServer::_engines;
bool GameServer::_is_running=true;

//funkcje pomocnicze
std::string getPort(std::string &request){
  boost::regex rgxPort("(?<=<port>)(.*)(?=</port>)");
  boost::smatch matchPort;
  if(boost::regex_search(request,matchPort ,rgxPort)){
    return matchPort[0];
  }else{
    return "";
  }
  
}

std::string getIp(std::string &request){
  boost::regex rgxIp("(?<=<ip>)(.*)(?=</ip>)");
  boost::smatch matchIp;
if(boost::regex_search(request,matchIp ,rgxIp)){
    return matchIp[0];
  }else{
    return "";
  }
}

std::string getName(std::string &request){
  boost::regex rgxIp("(?<=<name>)(.*)(?=</name>)");

  boost::smatch matchIp;
if(boost::regex_search(request,matchIp ,rgxIp)){
    return matchIp[0];
  }else{
    return "";
  }
}


bool gameExist(std::string name,const std::vector<std::shared_ptr<GameEngine>>& engines){
  for(std::shared_ptr<GameEngine> engine_ptr : engines){
    if(engine_ptr.get()->_name==name){
      return true;
    }
  }
      return false;
}

GameServer::GameServer(){
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

GameServer & GameServer::get(){
        static GameServer gameServer;
        return gameServer;
}



std::vector<player_ptr> GameServer::getPlayers(){

}

void GameServer::data_collector(const std::shared_ptr<tcp::tcp_client>& client,const tcp::tcp_client::read_result& res){
  if (res.success) {
    std::cout << "Otrzymano dane: " <<std::endl;
    std::string str = std::string(res.buffer.begin(), res.buffer.end());
    std::cout<< "Klient:"<< client->get_host() << "Wysyła: " <<str<<std::endl;
    //Wyrażenie regularne sprawdzające długosc kolejnego buffora <length=?/>
    if(strspn(str.c_str(), "0123456789") == str.size() ){
      std::cout << "Otrzymano długość komendy"<<std::endl;
      int i = stoi(str);
      GameServer::_buffer_length = strtoul (std::to_string(i).c_str(), NULL, 0);
    }else{
      std::cout << "Otrzymano komende"<<std::endl;
      str = "<ip>"+client->get_host()+"</ip><port>"+std::to_string(client->get_port())+"</port>"+str;
      GameServer::_queue_requests.push(str);
      //przygotowanie buffora na przyjecie kolejnej dlugosci
      GameServer::_buffer_length = 3;
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
    std::cout << "Nowy klient dołączył do gry " <<client->get_host()<< std::endl;
    GameServer::_clients_ptr.push_back(client);
    for(std::shared_ptr<tcp::tcp_client> i : _clients_ptr){
      std::cout<<i->get_host()<<i->get_port()<<std::endl;
    }
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
boost::regex rgxJoin("(?<=<join>)(.*)(?=</join>)");
boost::smatch matchJoin;
boost::regex rgxCreate("(?<=<create>)(.*)(?=</create>)");
boost::smatch matchCreate;
//odczytanie "adresata"
std::string host = getIp(request);
std::string port = getPort(request);
std::string name = getName(request);

if(boost::regex_search(request,matchCreate ,rgxCreate)){
//  //sprawdzanie czy gra instnieje
  if(gameExist(matchCreate[0],_engines)){
    _queue_responses.push("<ip>"+host+"</ip><port>"+port+
    "</port><msg>Gra o podanej nazwie istnieje. Wybierz innną nazwę</msg>");
  }else{
    _queue_responses.push("<ip>"+host+"</ip><port>"+port+"</port><msg>Utworzono grę</msg>");
//  //utworzenie gry
    
    //narusza pamięć       
    std::vector<std::shared_ptr<tcp::tcp_client>>::iterator it1= std::find_if(_clients_ptr.begin(), _clients_ptr.end(), 
    [&host,&port](std::shared_ptr<tcp::tcp_client> const& i){ return i.get()->get_host() == host &&
    i.get()->get_port()==atoi(port.c_str()); });
  
    std::vector<std::shared_ptr<GameEngine>>::iterator it2= std::find_if(_engines.begin(), _engines.end(), 
    [&matchCreate](std::shared_ptr<GameEngine> const& i){ return i.get()->_name == matchCreate[0]; });
    // naruszenie
    _engines.push_back(std::make_shared<GameEngine>(matchCreate[0],name,*it1));
    std::cout<<"WYPISYWANIE KLIENTOW"<<std::endl;
    _engines.back()->_queue.push("HANDSHAKE");
    std::cout<<"WYPISYWANIE GIER"<<std::endl;
    for(std::shared_ptr<GameEngine> engine : _engines) std::cout<<"name: "<<engine.get()->_name<<std::endl;

  }
}
    if(boost::regex_search(request,matchJoin ,rgxJoin)){
      std::cout<<"join"<<std::endl;
      for(std::shared_ptr<GameEngine> engine : _engines) std::cout<<"name: "<<engine.get()->_name<<std::endl;
      std::vector<std::shared_ptr<GameEngine>>::iterator it0 = find_if(_engines.begin(), _engines.end(),
     [&matchJoin] (const std::shared_ptr<GameEngine>& engine) { return engine->_name == matchJoin[0]; });

  std::vector<std::shared_ptr<tcp::tcp_client>>::iterator it1 = find_if(_clients_ptr.begin(), _clients_ptr.end(),
     [&host,&port] (const std::shared_ptr<tcp::tcp_client>& _client_ptr) {
        return _client_ptr->get_host() == host && _client_ptr->get_port() == atoi(port.c_str());
         });
     if(it0 != _engines.end()){

       (*it0)->addPlayer(name,*it1);
       (*it0)->_queue.push("HANDSHAKE");
       _queue_responses.push("<ip>"+host+"</ip><port>"+port+"</port><msg>Dołączonono do gry</msg>");
     }else{
       std::cout<<"Gra nie istnieje"<<std::endl;
      _queue_responses.push("<ip>"+host+"</ip><port>"+port+"</port><msg>Gra o podanej nazwie nie istnieje. Wybierz innną nazwę</msg>");
     }
    }else{}
   }
   }
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
        std::cout<<":"<<host<<":"<<port;//<<atoi(port.c_str())<<":"<<std::endl;
        std::vector<std::shared_ptr<tcp::tcp_client>>::iterator it1 = find_if(_clients_ptr.begin(), _clients_ptr.end(),
     [&host,&port] (const std::shared_ptr<tcp::tcp_client>& _client_ptr) {
        return _client_ptr->get_host() == host && _client_ptr->get_port() == atoi(port.c_str());
         });
        for(std::shared_ptr<tcp::tcp_client> client_ptr : _clients_ptr) std::cout<<client_ptr.get()->get_host()<<client_ptr.get()->get_port()<<std::endl;
        if(it1 !=_clients_ptr.end()){
          std::cout<<"Do klienta"<<(*it1)->get_host()<<std::endl;
          std::vector<char> sendable(response.begin(), response.end());
          (*it1)->async_write({sendable, nullptr});
        }else{
          std::cout<<"nie znaleziono klienta"<<std::endl;
        }

    }
  }
}

void GameServer::queue_result(std::string result){
  _queue_responses.push(result);
}



