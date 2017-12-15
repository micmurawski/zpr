#include "map_point.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>

using namespace std;

std::string MapPoint::toString(unsigned int player_id){
	string s= "#" +to_string(ID_)+"#"+to_string(0)+ "#" + to_string(id_)+"#"+ to_string(connections_.size())+"#" ;
	for( auto v : connections_)
		s = s+to_string(v)+"#";
	s= s+to_string(x_)+"#"+ to_string(y_) +"#"+resources_.toStringDataOnly();
	return s; 
	}
void MapPoint::loadFromString (std::string data){
	//splitting string by "#"
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of("#"));
	//setting class variables using individual values in vector
	id_=stoi(vec[0]);
	int connections_size=stoi(vec[1]);
	//setting connections' id
	for_each(vec.begin()+2, vec.begin()+connections_size+2, [&] (auto v) {connections_.push_back(stoi(v));});
	x_ = stoi(*(vec.begin()+connections_size+2));
	y_ = stoi(* (vec.begin()+connections_size+3));
	Resources r;
	r.loadFromString(vec.back());
	resources_=r;
	}

unsigned int MapPoint::getType(){
	return ID_;
	}

std::shared_ptr<GameObject> MapPoint::create(){
	return make_shared<MapPoint>();
	}

unsigned int MapPoint::ID_ = 0;
