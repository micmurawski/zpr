#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include "ship.hpp"
#include "building.hpp"
#include "resources.hpp"


class Player{
public:
std::vector<Ship> ships;
std::vector<Building> buildings;

private:
	Resources resources_;
};

#endif //PLAYER_HPP
