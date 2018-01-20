#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include <vector>
#include <iostream>
#include "../tcp/tcp.hpp"
#include "../game_objects/player.hpp"
#include "game_engine.hpp"
#ifdef _WIN32
#include <Winsock2.h>
#include <list>
#include <boost/regex.hpp>
#include <queue>
#include <thread>
#endif /* _WIN32 */
/**
 * \class GameServer
 *
 * Definicja klasy GameServer, która realizuje serwer gry
 * \author $Author: Michał Murawski, Marcin Brzykcy $
 *
 *
 */
class GameServer {
private:
    static std::mutex m_;
    static tcp::tcp_server _server;
    static long unsigned int _buffer_length;
    static std::queue<std::string> _queue_requests;
    static std::queue<std::string> _queue_responses;
    std::thread *_thread_requests = nullptr;
    std::thread *_thread_responses = nullptr;
    void process_queue_request();
    void process_queue_response();
    ///void kickPlayer(const std::shared_ptr<tcp::tcp_client>& client);
    static bool _is_running;
    std::shared_ptr<GameEngine> findGameEngine(std::string name);
    std::shared_ptr<tcp::tcp_client> findTCPClient(std::string host,std::string port);
    void run();
    /**
 	* Konstruktor klasy
 	*/
    GameServer(void);
    /**
 	* Destruktor
 	*/
    ~GameServer(void);
public:
    
    std::string _name="server";
    /**
 	* Funkcja zwracająca statyczny obiekt klasy
 	*/
    static GameServer & getInstance();
    static void pushToQueueResponse(std::string str);
    /**
 	* Funkcja umieszczająca w kolejce wynik do wysłania
    * \param[in] result 
 	*/
    void queue_result(std::string result);
    /**
 	* wektor przechowywanych wskaźników na instacje gry 
 	*/
    static std::vector<std::shared_ptr<GameEngine>> _engines;
    /**
 	* wektor przechowywanych wskaźników na klientów tcp podłączonych do serwera
 	*/
    static std::vector<std::shared_ptr<tcp::tcp_client>> _clients_ptr;
    /**
 	* Funkcja agregująca dane w serwerze
    * \param[in] client referencja na wskaźnik klienta wysyłającego dane do serwera
    * \param[in] client referencja na wskaźnik struktury  read_result
 	*/
    static void data_collector(const std::shared_ptr<tcp::tcp_client>& client, const tcp::tcp_client::read_result& res);
     /**
 	* Fukcja uruchamijąca serwer
    * \param[in] host
    * \param[in] port
 	*/
    void start(const std::string& host, std::uint32_t port);
    /**
 	* Fukcja Zwracająca liste graczy
    * \return zwraca wektor wskaźników na graczy
 	*/
    std::vector<player_ptr>  getPlayers();
    std::string getLobby();

};

#endif // GAME_SERVER_HPP