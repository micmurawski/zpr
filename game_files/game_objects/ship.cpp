#include "ship.hpp"
#include <memory>
#include <string>
#include <boost/algorithm/string.hpp>
#include <algorithm>

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
	//splitting string by "#"
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of("#"));
	//setting class variables using individual values in vector
	id_ = stoi(vec[0]);
	map_point_id_=stoi(vec[1]);
	hp_=stoi(vec[2]);
	}
	
unsigned int Ship::getType(){
	return ID_;
	}
	
std::shared_ptr<GameObject> Ship::create(){
	return make_shared<Ship>();
	}
unsigned int Ship::getHP(){
	return hp_;
}
unsigned int Ship::ID_ = 0;
