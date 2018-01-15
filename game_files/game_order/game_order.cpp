#include "game_order.hpp"
#include "../typedefs.hpp"
#include "../get_regex_function.hpp"
#include <cstring>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

MoveOrder::MoveOrder(std::string data){
	ship_id_vector_= make_unique<vector<unsigned int>>();
    string ships = getRegex(data, "(?<=<ships>)(.*)(?=</ships>)");
    //odczytywanie statkow
    std::vector<std::string> vec;
	boost::split(vec, ships, boost::is_any_of("#"));
	for_each(vec.begin(), vec.end()-1, [&] (auto v) {ship_id_vector_->push_back(stoi(v));});
	string destination = getRegex(data, "(?<=<destination>)(.*)(?=</destination>)");
	destination_id_ = stoi(destination);
	}
	
string MoveOrder::toString() const{
    string s = "<order><move><ships>";
    for (auto v : *ship_id_vector_){
        s=s+to_string(v)+"#";
        }
    s=s+"</ships><destination>";
    s=s+std::to_string(destination_id_)+"</destination></move></order>";
    return s;
	}

BuildOrder::BuildOrder(string data){
	string destination = getRegex(data, "(?<=<destination>)(.*)(?=</destination>)");
	point_id_ = stoi(destination);
	}
	
string BuildOrder::toString() const{
    string s = "<order><build>";
    s=s+"<destination>"+to_string(point_id_) + "</destination></build></order>";
    return s;
}
	
CreateShipOrder::CreateShipOrder(std::string data){
	string destination = getRegex(data, "(?<=<destination>)(.*)(?=</destination>)");
	point_id_ = stoi(destination);
	}
	
string CreateShipOrder::toString() const{
    string s = "<order><create>";
    s=s+"<destination>"+to_string(point_id_) + "</destination></create></order>";
    return s;
	}

