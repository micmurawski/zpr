#include "map_point.hpp"
#include <boost/algorithm/string.hpp>
#include "../get_regex_function.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

std::string MapPoint::toString(unsigned int player_id){
    string s= "<map_point><x>"+to_string(x_)+"</x><y>"+to_string(y_)+"</y><connections>";
	for( auto v : connections_)
		s = s+to_string(v)+"#";
    s= s+"</connections>"+resources_.toString()+"</map_point>";
	return s; 
	}
void MapPoint::loadFromString (std::string data){
    connections_.clear();
    string x = getRegex(data,"(?<=<x>)(.*)(?=</x>)");
    x_ = stoi(x);
    string y = getRegex(data,"(?<=<y>)(.*)(?=</y>)");
    y_ = stoi(y);
    string connections = getRegex(data,"(?<=<connections>)(.*)(?=</connections>)");
    //dzielenie connections uzywajac "#"
	std::vector<std::string> vec;
    boost::split(vec, connections, boost::is_any_of("#"));
    for_each(vec.begin(), vec.end()-1, [&] (auto v) {connections_.push_back(stoi(v));});
    string resources = getRegex(data,"(?<=<resources>)(.*)(?=</resources>)");
    resources_.loadFromString(resources);
	}

unsigned int MapPoint::getType(){
	return ID_;
	}

std::shared_ptr<GameObject> MapPoint::create(){
	return make_shared<MapPoint>();
	}

unsigned int MapPoint::ID_ = 0;
