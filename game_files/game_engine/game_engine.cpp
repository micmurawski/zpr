#include "game_engine.hpp"

std::vector<player_ptr> GameEngine::_players;
GameEngine::GameEngine(){
    start();
}

GameEngine::~GameEngine(){
    _is_running=false;
     if (_thread != nullptr) {
            _thread->join();
            delete _thread;
        }
}

GameEngine & GameEngine::get(){
        static GameEngine engine;
        return engine;
    }

void GameEngine::run(){
    while(_is_running){
        while(!_queue.empty()){
        processInput(_queue.front());
        _queue.pop();
        for(std::shared_ptr<tcp::tcp_client> client: GameServer::get()._clients_ptr){
            client->async_write({{'k','u','k','l','e'}, nullptr});
        }
        }
    }
    }

void GameEngine::sendCmd(std::string input,std::string host){
        _queue.push("<ip>"+host+"</ip>"+input);
        
    }

void GameEngine::start(){
        _thread = new std::thread(&GameEngine::run, this);
    }



void GameEngine::processInput(std::string input){
        std::string result = "";
        switch (_currentState)
    {
        case WAIT_FOR_PLAYERS:
            result = join(input);
        break;
        case GAME_INIT:
             result = gameInit();
        break;
        case PLAYING:

        break;
        
    }
        _currentState = _nxtState;
    }

void GameEngine::removePlayer(std::shared_ptr<tcp::tcp_client> client){
        int i=0;
        for (i=0;i<_players.size(); ){
                if(_players[i]->host_==client->get_host()){
                        _players.erase(_players.begin() + i);
                        std::vector<player_ptr>(_players.begin(), _players.end()).swap(_players);
                        
                }else{
                    i++;
                }
        }
            
        
    }

int GameEngine::getPlayers(){
        return _players.size();
    }

int GameEngine::state(){
        return _currentState;
    }

std::string GameEngine::join(std::string _str){
        
        std::cout<<"oczekiwanie na graczy ... "<<std::endl;
        //komenda dołączenia do gry
        boost::regex rgx("(?<=<join>)(.*)(?=</join>)");
        boost::smatch match;
        boost::regex rgx1("(?<=<ip>)(.*)(?=</ip>)");
        boost::smatch match1;
        if(boost::regex_search(_str,match ,rgx) && boost::regex_search(_str,match1 ,rgx1)){
            _players.push_back(std::make_shared<Player>(match[0],match1[0]));
            _nxtState = GAME_INIT;
            if(_players.size()==2){
                _nxtState = GAME_INIT;
                return "STATE=GAME_INIT";
                std::cout<<"dołączyli dwaj gracze..."<<std::endl;
                for(player_ptr p : _players) std::cout<<p->name_<<std::endl;
            }else{
                _nxtState = WAIT_FOR_PLAYERS;
                return "STATE=WAIT_FOR_PLAYERS";
            }
            
        }else{
            _nxtState = WAIT_FOR_PLAYERS;
            return "STATE=WAIT_FOR_PLAYERS";
        }
       
    }

std::string GameEngine::gameInit(){
        std::cout<<"rysowanie gry..."<<std::endl;
        std::cout<<"wysyłanie stanu początkowego..."<<std::endl;
        _nxtState = PLAYING;
        return "STATE=WAIT_FOR_PLAYERS";
        }

std::string GameEngine::playing(std::string _str){
        if(true){
            std::cout<<"czekanie na ruch graczy..."<<std::endl;
            _nxtState = PLAYING;
            return "STATE=PLAYING";
        }else{
            std::cout<<"zakonczenie gry..."<<std::endl;
            _nxtState = GAME_OVER;
            return "STATE=GAME_OVER";
        }
        
        }