#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <memory>
#include "ship.hpp"
#include "building.hpp"
#include "resources.hpp"
#include "string"
#include "../tcp/tcp.hpp"

/**
 * \class Player
 *
 * Definicja klasy Player, która przechowuje informacje o stanie gracza w grze
 * \author $Author: Michał Murawski, Marcin Brzykcy $
 *
 *
 */

class Player: public GameObject{
	public:
		std::vector<std::shared_ptr<Ship>> ships_;
		std::vector<std::shared_ptr<Building>> buildings_;
		std::shared_ptr<tcp::tcp_client>  _client_ptr;
		Resources resources_;
		std::string name_;
		std::string host_;
		unsigned int id_;
		bool _finished = false;
        unsigned int getId(){return id_;}
		std::string get_name() {return name_;}
		void set_name(std::string name) {name_ = name;}
        std::string toString();
        void loadFromString(std::string data);

		/**
 		* Konstruktor klasy
 		*
 		* \param[in] name Nazwa gracza
 		* \param[in] client_ptr wskaźnik na klienta protokołu tcp.
 		* 
 		*/
		Player(std::string name,const std::shared_ptr<tcp::tcp_client>& client_ptr=nullptr){
			name_=name;
			_client_ptr = client_ptr;

		}
		/**
 		* Funkcja obliczająca sumę obrażeń w punkcie mapy podczas bitwy
 		*
 		* \param[in] i id punktu mapy
 		* 
 		*/
		int getDamageAtNode(int i){
			int sum = 0;
			for(std::shared_ptr<Ship> ship_ptr : ships_){
				if(ship_ptr.get()->getMapPointId()==i){
					sum+=ship_ptr.get()->getDamage();
				}
			}
			return sum;
		}
				/**
 		* Funkcja zadająca obrażenia statkom w punkcie
 		*
 		* \param[in] i id punktu mapy
  		* \param[in] dmg obrażenia
 		* 
 		*/
		void modifyHpAtNodeOfAllShips(int i,int dmg){
			int N=0;
			for(std::shared_ptr<Ship> ship_ptr : ships_){
				if(ship_ptr.get()->getMapPointId()==i){
					N++;
				}
			}

			for(std::shared_ptr<Ship> ship_ptr : ships_){
				if(ship_ptr.get()->getMapPointId()==i){
					ship_ptr.get()->modifyHP(-dmg/N);
				}
			}

		}

};

#endif //PLAYER_HPP
