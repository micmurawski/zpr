#include "game_order.hpp"
#include "../typedefs.hpp"
#include <cstring>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

MoveOrder::MoveOrder(std::string data){
	ship_id_vector_ = make_unique<vector<unsigned int>>();
	//splitting string by "#"
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of("#"));
	//setting class variables using individual values in vector
	//firs two are start_point_id_ and destination_id_
	start_point_id_=stoi(vec[0]);
	destination_id_ = stoi(vec[1]);
	//others are vector of ships' id
	for_each(vec.begin()+2, vec.end(), [&] (auto v) {ship_id_vector_->push_back(stoi(v));});
	
	}
	
string MoveOrder::toString(){
	string s;
	s = "#" + to_string(MoveOrder::type)+ "#"+ to_string(start_point_id_) + "#" + to_string(destination_id_);
	for (auto v : *ship_id_vector_){
		s=s+"#"+to_string(v);
		}
	return s;
	}
	
CreateShipOrder::CreateShipOrder(std::string data){
	//splitting string by "#"
	std::vector<std::string> vec;
	boost::split(vec, data, boost::is_any_of("#"));
	//setting class variables using individual values in vector
	point_id_=stoi(vec[0]);
	ship_type_ = stoi(vec[1]);
	}
	
string CreateShipOrder::toString(){
	string s;
	s= "#" + to_string(CreateShipOrder::type) + "#" + to_string(point_id_) + "#" + to_string(ship_type_);
	return s;
	}

