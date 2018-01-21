#include "building.hpp"
#include "../get_regex_function.hpp"
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>


using namespace std;

string Building::toString(){
    string s= "<building><point>"+to_string(point_id_)+"</point></building>";
        return s;
        }

void Building::loadFromString (std::string data){
    string s = getRegex(data,"(?<=<point>)(.*)(?=</point>)");
    point_id_=static_cast<int> (stoi(s));
        }


