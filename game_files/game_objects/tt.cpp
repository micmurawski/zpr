#include "../game_order/game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include <memory>
#include "../game_order/order_decoder.hpp"
#include "game_object_factory.hpp"
#include "game_object.hpp"
#include "map_point.hpp"

using namespace std;



int main(){

		
	Resources r(500);
	Building building(12);

	shared_ptr<Player> player = make_shared<Player>("player");
	
	player->resources_=r;
	player->ships_.push_back(make_shared<Ship>(12,13));
	player->ships_.push_back(make_shared<Ship>(32,123));
	player->buildings_.push_back(make_shared<Building>(12));
	player->id_=3;
	shared_ptr<Player> player2 = make_shared<Player>("player2");
	Resources r2(300);
	player2->resources_=r2;
	player2->ships_.push_back(make_shared<Ship>(1,3));
	player2->ships_.push_back(make_shared<Ship>(322,1213));
	player2->buildings_.push_back(make_shared<Building>(12));
	player2->buildings_.push_back(make_shared<Building>(124));
	player2->buildings_.push_back(make_shared<Building>(112));
	player2->id_=2;
	GameState game_state;
	game_state.players_.push_back(player);
	game_state.players_.push_back(player2);
	cout<<endl;

	GameState game_state2;
	game_state2.loadFromString(game_state.toString());

	
	if((game_state.toString()).compare(game_state2.toString())){
		}else cout<<"zapisywanie do string i odczytywanie poprawne";
	


	return 0;
}
