#include "game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include "order_decoder.hpp"
#include "game_object_factory.hpp"
#include "game_object.hpp"
#include "map_point.hpp"

using namespace std;



int main(){

	GameObjectFactory& factory = GameObjectFactory::get_instance();
	Ship::ID_ = factory.registerObject(Ship::create);
	MapPoint::ID_ = factory.registerObject(MapPoint::create);
	Resources::ID_ = factory.registerObject(Resources::create);
	
	Ship ship(12, 13);
	vector<string>vec;
	vec.push_back(ship.toString(2)); //the number in the function argument is players number
	
	Resources r(500);
	vec.push_back(r.toString(1)); //the number in the function argument is players number
	
	vector<unsigned int> connections;
	connections.push_back(3);
	connections.push_back(5);
	connections.push_back(8);
	connections.push_back(2);
	MapPoint point(10, connections, 4, 7, r);
	vec.push_back(point.toString(1));
	
	//function decode creates new GameState object that represents current situation in game
	shared_ptr<GameState> gamestate = factory.decode(vec);
	
	cout<<endl<<vec[0];
	cout<<endl<<(gamestate->players_[2]->ships_[0]->toString());
	cout<<endl<<vec[2];
	cout<<endl<<(gamestate->map_points_[0]->toString());
	cout<<endl<<vec[1];
	cout<<endl<<(gamestate->players_[1]->resources_.toString());


	return 0;
}
