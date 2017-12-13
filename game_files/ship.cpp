#include "ship.hpp"
#include <memory>
#include <string>

using namespace std;

void Ship::modifyHP(int hp) {
		hp_ +=hp;
		if(hp_<0)
			hp_ = 0;
		}



std::string Ship::toString(unsigned int player_id){
	string s ="#"+to_string(ID_)+ "#" + to_string(player_id) + "#" + to_string(id_) + "#"+ to_string(map_point_id_) + "#" + to_string(hp_);
	return s;
	}
	
void Ship::loadFromString (std::string data){
	
	}
	
unsigned int Ship::getType(){
	return ID_;
	}
	
std::shared_ptr<GameObject> Ship::create(){
	return make_shared<Ship>();
	}

unsigned int Ship::ID_ = 0;
