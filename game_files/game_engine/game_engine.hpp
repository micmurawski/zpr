#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "../typedefs.hpp"
#include "../tcp/tcp.hpp"
#include <string>
#include <boost/regex.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <queue>

/**
 * \class GameEngine
 *
 * Definicja klasy GameEngine, która jest instancją gry.
 * \author $Author: Michał Murawski, Marcin Brzykcy $
 *
 *
 */

class GameEngine{
private:
    // wektor wskaźników na graczy
    std::vector<player_ptr> _players;
    //stany gry
    enum state {WAIT_FOR_PLAYERS=0,WAIT_FOR_MOVE=1,COMPUTE_NEW_STATE=2,GAME_OVER=3};
    //obecny stan gry
    state _currentState=WAIT_FOR_PLAYERS;
    //następny stan gry
    state _nxtState;
public:
    std::string _name;
    //kolejka przetwarzanych danych przez instacje gry
    std::queue<std::string> _queue;
    //funkcja uruchamijąca wątek prztwarzania kolejki
    void run();
    //funkcja zatrzymująca wątek przetwarzania kolejki
    void stop();
    //wskaźnik na wątek przetwarzający kolejke
    std::thread *_thread = nullptr;
    //pole stanu przetwarzania kolejki
    bool _is_running=true;
    //funkcja wysyłająca komendy do graczy i serwera
    void sendCmd(std::string input);
    //funkcja uruchamijąca gre
    void start();
    //fukcja przetwarzające dane w kolejce
    void processInput(std::string input);
    //funkcja usuwająca gracza z gry
    int removePlayer(const std::shared_ptr<tcp::tcp_client>& client);
    //funkcja dodająca gracza do gry
    void addPlayer( std::string name,const std::shared_ptr<tcp::tcp_client>& _client_ptr);
    std::vector<player_ptr> getPlayers();
    /**
 		* funkcja zwracająca stan gry
 		*
 		* \return liczba reperezentująca stan gry
 		*/
    int state();
    /**
 		* Konstruktor klasy
 		*
 		* \param[in] name Nazwa gry
 		* \param[in] nazwa gracza który utworzył gre
        * \param[in] referencja na wskaźnik klienta tcp który utworzył gre
 		* 
 	*/
    GameEngine(std::string _name,std::string _mastername,const std::shared_ptr<tcp::tcp_client>& master);
     /**
 		* Destruktor klasy
 	*/
    ~GameEngine();
protected:
    /**
 	* Funkcja dołaczająca gracza do gry na podstawie stringa
 	* \return odpowiedź gry
 	*/
    std::string join(std::string _str);
    /**
 	* Funkcja inicjalizująca gre
 	* \return odpowiedź gry
 	*/
    std::string gameInit();
    std::string playing(std::string _str);

};


#endif //GAME_ENGINE_HPP