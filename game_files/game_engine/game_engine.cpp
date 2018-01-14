#include "game_engine.hpp"
#include "game_server.hpp"


//funkcje pomocnicze
std::string getRegex(std::string &request,std::string pattern){
  boost::regex rgxIp(pattern);
  boost::smatch matchIp;
    if(boost::regex_search(request,matchIp ,rgxIp)){
        return matchIp[0];
    }else{
        return "";
    }
}

GameEngine::GameEngine(std::string _name,std::string _mastername,const std::shared_ptr<tcp::tcp_client>& master){
    addPlayer(_mastername,master);
    std::cout<<"ENGINE CREATED"<<std::endl;
    GameEngine::_name=_name;
    std::cout<<"nazwa serwera: "<<GameServer::get()._name<<std::endl;
    std::cout<<"nazwa: "<<GameEngine::_name<<std::endl;
    _thread = new std::thread(&GameEngine::run, this);
}

GameEngine::~GameEngine(){
    stop();
    std::cout<<"ENGINE DESTROYED"<<std::endl;  
}

void GameEngine::stop(){
    std::cout<<"STOP"<<std::endl;
    _is_running=false;
    try{
    if(_thread->joinable()){
        _thread->join();
        std::cout<<"join"<<std::endl;
    }
    }catch(std::system_error& x){
        std::cout<<x.what()<<std::endl;
    }
}


void GameEngine::run(){
    std::cout<<"ROZPOCZYNANIE RUN ENGINE"<<std::endl;
    while(_is_running){
        while(!_queue.empty()){
        std::cout<<"GAME ENGINE"<<_name<<" "<<_queue.front()<<std::endl;
        processInput(_queue.front());
        _queue.pop();
        }
    }
}

void GameEngine::sendCmd(std::string input){
        std::cout<<"Wysłano: "+input<<std::endl;
        _queue.push(input);
}



void GameEngine::processInput(std::string input){
    std::cout<<"PRZETWARZANIE KOMENDY... "<<input<<std::endl;
    std::cout<<"LICZBA GRACZY "<<_players.size()<<std::endl;
    std::string host = getRegex(input,"(?<=<ip>)(.*)(?=</ip>)");
    std::string port = getRegex(input,"(?<=<port>)(.*)(?=</port>)");
    std::vector<player_ptr>::iterator it;
    for(player_ptr player:_players) std::cout<<player.get()->name_<<std::endl;
    std::cout<<"STAN OBECNY "<<_currentState<<std::endl;
    std::string result = "";
        switch (_currentState){
        case WAIT_FOR_PLAYERS:
            if(_players.size()==2){
                std::cout<<"Dołączyła odpowiednia ilość graczy"<<std::endl;
                for(player_ptr player : _players){
                    std::cout<<"name "<<player->name_<<std::endl;
                    std::cout<<"host "<<player->_client_ptr->get_host()<<std::endl;
                    std::cout<<"port "<<player->_client_ptr->get_port()<<std::endl;
                }
                
                result="<state>WAIT_FOR_PLAYERS</state><msg>Dołączyła odpowiednia ilość graczy. Rozpoczynanie gry...</msg>";
                //Tutaj następuje inicjalizacjia gry i wysłanie stanu gry do graczy
                for(player_ptr player : _players){
                    GameServer::get().queue_result("<ip>"+player->_client_ptr->get_host()+"</ip>"+
                    "<port>"+std::to_string(player->_client_ptr->get_port())+"</port>"+"<cmd>STAN GRY</cmd>");
                }
                _nxtState= WAIT_FOR_MOVE;
            }else{
                std::cout<<"Oczekiwanie na graczy..."<<std::endl;
                for(player_ptr player : _players){
                    std::cout<<"name "<<player->name_<<std::endl;
                    std::cout<<"host "<<player->_client_ptr->get_host()<<std::endl;
                    std::cout<<"port "<<player->_client_ptr->get_port()<<std::endl;
                }
                _nxtState=WAIT_FOR_PLAYERS;
                result="<state>WAIT_FOR_PLAYERS</state><msg>Oczekiwanie na graczy</msg>";
                for(player_ptr player : _players){
                    GameServer::get().queue_result("<ip>"+player->_client_ptr->get_host()+"</ip>"+
                    "<port>"+std::to_string(player->_client_ptr->get_port())+"</port>"+result);
                }
                
            }
            
        break;
        case WAIT_FOR_MOVE:
             std::cout<<"GRACZE WYKONUJA RUCH"<<std::endl;
             //sprawdzanie czy gracz wykonał ruch
             
            it= std::find_if(_players.begin(), _players.end(), 
                [&host,&port](player_ptr const& i){ 
                    return i.get()->_client_ptr->get_host() == host &&
                i.get()->_client_ptr->get_port()==atoi(port.c_str()); });
            if(it != _players.end()){
                if((*it)->_finished){
                    //wykonano ruch
                    GameServer::get().queue_result("<ip>"+(*it)->_client_ptr->get_host()+"</ip>"+
                    "<port>"+std::to_string((*it)->_client_ptr->get_port())+"</port><msg>"+"Wykonano rych"+"</msg>");
                }else{
                    (*it)->_finished=true;
                    GameServer::get().queue_result("<ip>"+(*it)->_client_ptr->get_host()+"</ip>"+
                    "<port>"+std::to_string((*it)->_client_ptr->get_port())+"</port><msg>"+"Dziękuje za wykonanie ruchu oczekujemy na reszte graczy"+"</msg>");
                }
                if(all_of(_players.begin(), _players.end(),[](player_ptr const& i){ return i.get()->_finished == true; })){
                    std::cout<<"Wszyscy gracze wykonali ruch. Następuje obliczanie nowego stanu gry"<<std::endl;
                    for(player_ptr player : _players){
                        player->_finished=false;
                    GameServer::get().queue_result("<ip>"+player->_client_ptr->get_host()+"</ip>"+
                    "<port>"+std::to_string(player->_client_ptr->get_port())+"</port>"+"<cmd>STAN GRY</cmd>");
                    }
                }
            }else{

            }
        break;
        //case COMPUTE_NEW_STATE:

        //break;
        case GAME_OVER:

        break;
        
    }
        _currentState = _nxtState;
    }

//void GameEngine::removePlayer(const std::shared_ptr<tcp::tcp_client>& client){
//        int i=0;
//        for (i=0;i<_players.size(); ){
//                if(_players[i]->_client_ptr->get_host()==client->get_host()){
//                        _players.erase(_players.begin() + i);
//                        std::vector<player_ptr>(_players.begin(), _players.end()).swap(_players);
//                        
//                }else{
//                    i++;
//                }
//        }
//            
//        
//    }
//
std::vector<player_ptr> GameEngine::getPlayers(){
        return _players;
    }

int GameEngine::state(){
        return _currentState;
}

void GameEngine::addPlayer(std::string name,const std::shared_ptr<tcp::tcp_client>& _client_ptr){
    std::cout<<"addPlayer"<<std::endl;
     _players.push_back(std::make_shared<Player>(name,_client_ptr));
}


int GameEngine::removePlayer(const std::shared_ptr<tcp::tcp_client>& _client_ptr){
    _players.erase(
    std::remove_if(
    _players.begin(),
    _players.end(),
    [&_client_ptr](const player_ptr& _player){ return _player.get()->_client_ptr.get()==_client_ptr.get(); }
    ),
    _players.end());

    return _players.size();
}
