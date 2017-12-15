#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <memory>
#include "ship.hpp"
#include "building.hpp"
#include "resources.hpp"
#include "string"


class Player{
	public:
		std::vector<std::shared_ptr<Ship>> ships_;
		std::vector<std::shared_ptr<Building>> buildings_;
		Resources resources_;
		std::string name_;
		std::string host_;
		std::string get_name() {return name_;}
		void set_name(std::string name) {name_ = name;}
		Player(std::string name_ = "noname",std::string host_="127.0.0.1"): name_(name_), host_(host_){
		std::cout<<"Utworzon instancje nowego gracza "<<std::endl;
		std::cout<<"_name: "<<name_<<std::endl;
		std::cout<<"_host: "<<host_<<std::endl;
	}
	~Player(){
		std::cout<<"Usunięto instancje gracza "<<std::endl;
		std::cout<<"_name: "<<name_<<std::endl;
		std::cout<<"_host: "<<host_<<std::endl;
	}

	

};

#endif //PLAYER_HPP
