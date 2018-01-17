#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP
#include "../tcp/tcp.hpp"
#include <string>
#include <condition_variable>
#include <iostream>
#include<vector>
#include <mutex>
#include <math.h>
#include <signal.h>
#include <queue>
#ifdef _WIN32
#include <Winsock2.h>
#endif /* _WIN32 */

/**
 * \class GameClient
 *
 * Definicja klasy GameClient, która realizuje klienta gry
 * \author $Author: Michał Murawski, Marcin Brzykcy $
 *
 *
 */
class GameClient{

public:
static tcp::tcp_client _client;
static std::string _name;
static std::queue<std::string> _queue;
static std::mutex _m;
bool getState(){return wait_;};
/**
* Singleton
*/
static GameClient & get();
/**
* funkcja realizująca odczyt danych z protokołu tcp
*
* \param[in] client  klient tcp 
* \param[in] wskaźnik na strukturę odpowiedzi w protokole tcp
* 
*/
static void read(tcp::tcp_client& client, const tcp::tcp_client::read_result& res);
/**
* funkcja realizująca połączenie
*
* \param[in] host referencja na host gry zadany w stringu
* \param[in] port port serwera
* 
*/
static void connect(const std::string& host, std::uint32_t port);
/**
* funkcja realizująca wysyłanie komend przez gracza
*
* \param[in] cmd string komendy
* 
*/
static void sendCmd(std::string cmd);
/**
* funkcja realizująca dołączenie do gry gracza
*
* 
*/
static void join();
private:
void processQueue();
std::thread *_thread;
bool wait_=true;
bool _is_running=true;
GameClient();
/**
* Destruktor klasy
*/
~GameClient();


};


#endif //GAME_CLIENT_HPP