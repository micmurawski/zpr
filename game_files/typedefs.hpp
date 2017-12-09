#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <memory>
#include <vector>
#include "player.hpp"
#include "map_point.hpp"

typedef std::unique_ptr<Player> player_ptr;
typedef std::unique_ptr<MapPoint> map_point_ptr;
typedef std::unique_ptr <std::vector<unsigned int>> ship_vector_uptr;

#endif //TYPEDEFS_HPP
