#include "resources.hpp"
#include "../get_regex_function.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

string Resources::toString(){
    string s= "<resources><metal>"+to_string(metal_)+"</metal></resources>";
	return s; 
	}
	
void Resources::loadFromString (std::string data){
    string metal = getRegex(data,"(?<=<metal>)(.*)(?=</metal>)");
    metal_=stoi(metal);
	}

unsigned int Resources::getType(){
	return ID_;
	}

std::shared_ptr<GameObject> Resources::create(){
	return make_shared<Resources>();
	}

unsigned int Resources::ID_ = 0;
