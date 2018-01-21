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
    // mutex zabezpieczający singleton
    static std::mutex m_;
    // serwet tcp
    static tcp::tcp_server _server;
    //dlugosc buffora
    static long unsigned int _buffer_length;
    //kolejka przetwarzanych zapytan
    static std::queue<std::string> _queue_requests;
    //kolejka przetwarzanych odpowiedzi
    static std::queue<std::string> _queue_responses;
    //wskaźnik na wątek przetwarzania zapytań
    std::thread *_thread_requests = nullptr;
    //wskaźnik na wątek przetwarzanych odpowiedzi
    std::thread *_thread_responses = nullptr;
    //funkcja przetwarzająca zapytania
    void process_queue_request();
    //funkcja przetwarzająca odpowiedzi
    void process_queue_response();
    // flaga mówiąca o tym że wątki przetwarzają dane
    static bool _is_running;
    /**
 	* funkcja zwracająca game Engine dla zadanej nazwy
 	* \param name Nazwa gry
 	* \return std::shared_ptr na gameEngine
 	*/
    std::shared_ptr<GameEngine> findGameEngine(std::string name);
    /**
 	* funkcja zwracająca wskaźnik na klienta tcp o zadanym ip i porcie
 	* \param host host
    * \param port port
 	* \return std::shared_ptr na tcp::tcp_client
 	*/
    std::shared_ptr<tcp::tcp_client> findTCPClient(std::string host,std::string port);
    /**
    * funkcja inicjalizująca wątki do przetwarzania kolejek z zapytaniami i odpowiedziami serwera
 	*/
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
    /**
 	* Funkcja przekazująca dane do kolejki odpowiedzi
    * \param dane
 	*/
    static void pushToQueueResponse(std::string str);
    /**
 	* Funkcja umieszczająca w kolejce wynik do wysłania
    * \param result 
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
    * \param client referencja na wskaźnik klienta wysyłającego dane do serwera
    * \param client referencja na wskaźnik struktury  read_result
 	*/
    static void data_collector(const std::shared_ptr<tcp::tcp_client>& client, const tcp::tcp_client::read_result& res);
     /**
 	* Fukcja uruchamijąca serwer
    * \param host
    * \param port
 	*/
    void start(const std::string& host, std::uint32_t port);
    /**
 	* Fukcja Zwracająca liste graczy
    * \return zwraca wektor wskaźników na graczy
 	*/
    std::vector<player_ptr>  getPlayers();
    /**
 	* Fukcja Zwracająca liste gier
    * \return zwraca wektor wskaźników na graczy
 	*/
    std::string getLobby();

};

#endif // GAME_SERVER_HPP