#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include "../typedefs.hpp"
#include "../game_objects/game_object.hpp"
#include "../game_objects/ship.hpp"
#include "../game_objects/building.hpp"
#include "../game_objects/resources.hpp"
#include "../game_objects/map_point.hpp"

class GameState{
	public:
	GameState(unsigned int players_nr);
	void accept(game_object_ptr object);
	std::vector <player_ptr> players_;
	std::vector <map_point_ptr> map_points_;
	Ship ship_prototype_;
	MapPoint map_point_prototype_;
	Building building_prototype_;
	Resources resources_prototype_;
	};

	
#endif //GAME_STATE_HPP