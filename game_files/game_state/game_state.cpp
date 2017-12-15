#include "game_state.hpp"

using namespace std;

GameState::GameState(unsigned int players_number){
	for (int i = 0; i<players_number; i++)
		players_.push_back(make_unique<Player>());
	}

void GameState::accept(game_object_ptr object){
	//GameObject object = *(game_object);
	if(object->getType() == map_point_prototype_.getType())
		map_points_.push_back(dynamic_pointer_cast<MapPoint>(object));
	else if(object->getType() == ship_prototype_.getType())
		players_[object->player_id_]->ships_.push_back(dynamic_pointer_cast<Ship> (object));
	else if(object->getType() == building_prototype_.getType())
		players_[object->player_id_]->buildings_.push_back(dynamic_pointer_cast<Building> (object));
	else if(object->getType() == resources_prototype_.getType())
		players_[object->player_id_]->resources_ = *(dynamic_pointer_cast<Resources> (object));
	}
