#include "resources.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

std::string Resources::toString(unsigned int player_id){
	string s= "#" +to_string(ID_)+"#"+to_string(player_id)+"#"+toStringDataOnly();
	return s; 
	}
	
std::string Resources::toStringDataOnly(){
	string s =  to_string(metal_)+"R";
	return s;
	}
void Resources::loadFromString (std::string data){
	//splitting string by "$"
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of("R"));
	//setting class variables using individual values in vector
	metal_=stoi(vec[0]);
	}

unsigned int Resources::getType(){
	return ID_;
	}

std::shared_ptr<GameObject> Resources::create(){
	return make_shared<Resources>();
	}

unsigned int Resources::ID_ = 0;
