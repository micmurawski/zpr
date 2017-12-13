#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include "player.hpp"
#include "map_point.hpp"
#include "game_object.hpp"
#include "typedefs.hpp"

typedef std::unique_ptr<Player> player_ptr;
typedef std::shared_ptr<MapPoint> map_point_ptr;
typedef std::unique_ptr<std::vector<unsigned int>> ship_vector_uptr;
typedef std::shared_ptr<GameObject> game_object_ptr;
typedef std::shared_ptr<GameObject> (*createGameObject)();
typedef std::map<unsigned int, createGameObject> func_map;

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
