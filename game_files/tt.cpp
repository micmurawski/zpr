#include "game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include "order_decoder.hpp"
#include "game_object_factory.hpp"
#include "game_object.hpp"

using namespace std;



int main(){

	GameObjectFactory& factory = GameObjectFactory::get_instance();
	Ship::ID_ = factory.registerObject(Ship::create);
	
	Ship ship(12, 13);
	vector<string>vec;
	vec.push_back(ship.toString(2));
	shared_ptr<GameState> gamestate = factory.decode(vec);
	cout<<endl<<(gamestate->players_[2]->ships_[0]->getDamage());
	return 0;
}
