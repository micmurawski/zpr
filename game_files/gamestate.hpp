#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>
#include "player.hpp"
#include "map_point.hpp"
#include "typedefs.hpp"

struct GameState{
	std::vector <player_ptr> players_;
	std::vector <map_point_ptr> map_points_;
	};
#endif //GAME_STATE_HPP
