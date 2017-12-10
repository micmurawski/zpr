#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <memory>
#include <vector>
#include "player.hpp"
#include "map_point.hpp"
#include "game_sendable.hpp"
#include "game_order.hpp"

typedef std::unique_ptr<Player> player_ptr;
typedef std::unique_ptr<MapPoint> map_point_ptr;
typedef std::unique_ptr<std::vector<unsigned int>> ship_vector_uptr;

//typedef std::shared_ptr<GameOrder> gameorder_sptr;

#endif //TYPEDEFS_HPP
