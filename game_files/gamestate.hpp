#include <vector>
#include "player.hpp"
#include "map_point.hpp"

typedef player_ptr std::unique_ptr<Player>
typedef map_point_ptr std::unique_ptr<MapPoint>

class GameState{
public:
	
private:
	std::vector <player_ptr> players_;
	std::vector <map_point_ptr> map_points_;
	};
