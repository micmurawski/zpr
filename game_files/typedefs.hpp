#ifndef TYPEDEFS_HPP
#define TYPEDEFS_HPP

#include <memory>
#include <vector>
#include <map>
#include "game_objects/player.hpp"
#include "game_objects/ship.hpp"
#include "game_objects/map_point.hpp"
#include "game_objects/game_object.hpp"

typedef std::shared_ptr<Player> player_ptr;
//typedef std::unique_ptr<Planet> planet_ptr;
typedef std::unique_ptr<Ship> ship_ptr;
typedef std::shared_ptr<MapPoint> map_point_ptr;
typedef std::unique_ptr<std::vector<unsigned int>> ship_vector_uptr;
typedef std::shared_ptr<GameObject> game_object_ptr;
typedef std::shared_ptr<GameObject> (*createGameObject)();
typedef std::map<unsigned int, createGameObject> func_map;

#endif
