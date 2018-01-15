#include "player.hpp"
#include "../get_regex_function.hpp"

using namespace std;

string Player::toString(){
    string data= "<player><id>";
    data = data+to_string(id_)+"</id><name>";
    data = data + name_+"</name><ships>";
    for(auto ship : ships_){
        data = data+(ship->toString());
    }
    data=data+"</ships><buildings>";
    for(auto building : buildings_){
        data=data+building->toString();
    }
    data=data+"</buildings>";
    data=data+resources_.toString();
    data=data+"</player>";
    return data;
}
void Player::loadFromString(string data){
    ships_.clear();
    buildings_.clear();
    string id = getRegex(data,"(?<=<id>)(.*)(?=</id>)");
    id_=static_cast<unsigned int> (stoi(id));
    string name = getRegex(data,"(?<=<name>)(.*)(?=</name>)");
    name_=name;
    string resources = getRegex(data,"(?<=<resources>)(.*)(?=</resources>)");
    resources_.loadFromString(resources);
    //wczytywanie statkow
    string ships = getRegex(data,"(?<=<ships>)(.*)(?=</ships>)");
    while(ships.size()>0){
    string ship_str = ships.substr(ships.find("<ship>")+6, ships.find("</ship>")-6);
    shared_ptr<Ship> ship = make_shared<Ship>();
    ship->loadFromString(ship_str);
    ships_.push_back(ship);
    ships = ships.substr(ships.find("</ship>")+7);
        }
    //wczytywanie budynkow
    string buildings = getRegex(data,"(?<=<buildings>)(.*)(?=</buildings>)");
    while(buildings.size()>0){
    string building_str = buildings.substr(buildings.find("<building>")+10, buildings.find("</building>")-10);
    //cout<<endl<<"BUILDING"<<ship_str<<endl;
    shared_ptr<Building> building = make_shared<Building>();
    building->loadFromString(building_str);
    buildings_.push_back(building);
    buildings = buildings.substr(buildings.find("</building>")+11);
        }
}
