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
 * Definicja klasy Player, która przechowuje zasoby gracza w grze 
 * \author $Author: Michał Murawski, Marcin Brzykcy $
 *
 *
 */

class Player{
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
			std::cout<<"Utworzon instancje nowego gracza "<<std::endl;
			std::cout<<"_name: "<<name_<<std::endl;
			std::cout<<"_host: "<<_client_ptr->get_host()<<std::endl;
			std::cout<<"_port: "<<_client_ptr->get_port()<<std::endl;
		}
		/**
 		* Destruktor klasy
 		*/
		~Player(){
			std::cout<<"Usunięto instancje gracza "<<std::endl;
			std::cout<<"_name: "<<name_<<std::endl;
			std::cout<<"_host: "<<host_<<std::endl;
		}
	

	

};

#endif //PLAYER_HPP
