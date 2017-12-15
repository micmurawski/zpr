#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <memory>
#include <vector>
#include <map>
#include "player.hpp"
#include "map_point.hpp"
#include "game_order.hpp"
#include "game_state.hpp"
#include "game_object.hpp"
#include "ship.hpp"


typedef std::shared_ptr<MapPoint> map_point_ptr;
typedef std::unique_ptr<std::vector<unsigned int>> ship_vector_uptr;
typedef std::shared_ptr<GameObject> game_object_ptr;
typedef std::shared_ptr<GameObject> (*createGameObject)();
typedef std::map<unsigned int, createGameObject> func_map;



#endif //TYPEDEFS_HPP
