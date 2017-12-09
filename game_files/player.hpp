#include <vector>
#include "ship.h"
#include "building.h"

class Player{
public:
std::vector<Ship> ships;
std::vector<Building> buildings;

private:
	Resources resources_;
};
