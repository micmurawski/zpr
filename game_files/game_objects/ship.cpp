#include "ship.hpp"
#include <memory>
#include <string>
#include <boost/algorithm/string.hpp>
#include "../get_regex_function.hpp"
#include <algorithm>

using namespace std;

void Ship::modifyHP(int hp) {
		hp_ +=hp;
		if(hp_<0)
			hp_ = 0;
		}



std::string Ship::toString(unsigned int player_id){
    string s ="<ship><id>"+to_string(id_)+"</id><map_point>"+to_string(map_point_id_)+"</map_point></ship>";
	return s;
	}
	
void Ship::loadFromString (std::string data){
    string id = getRegex(data,"(?<=<id>)(.*)(?=</id>)");
    id_=static_cast<int> (stoi(id));
    string point= getRegex(data,"(?<=<map_point>)(.*)(?=</map_point>)");
    map_point_id_=static_cast<int> (stoi(point));
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
