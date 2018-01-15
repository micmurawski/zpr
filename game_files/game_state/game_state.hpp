#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include "../typedefs.hpp"
#include "../game_objects/game_object.hpp"
#include "../game_objects/ship.hpp"
#include "../game_objects/building.hpp"
#include "../game_objects/resources.hpp"
#include "../game_objects/map_point.hpp"
#include <algorithm>

class GameState{
	public:
	GameState();
	map_point_ptr getPointById(unsigned int id);
    //void accept(game_object_ptr object);
    void loadFromString(std::string data){};
	std::vector <player_ptr> players_;
    std::vector <map_point_ptr> map_points_;
	Ship ship_prototype_;
	MapPoint map_point_prototype_;
	Building building_prototype_;
	Resources resources_prototype_;
	void removeShips();
	int MapPointOwnerId(unsigned int map_point_id);
    int WhoHasFleet(unsigned int map_point_id);
    int WhoHasBuilding(unsigned int map_point_id);
    std::vector<std::shared_ptr<Ship>> FleetOnPoint(unsigned int map_point_id);
    bool isConnection(unsigned int map_point1, unsigned int map_point2);
	};

	
#endif //GAME_STATE_HPP
