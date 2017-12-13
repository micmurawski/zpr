#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>
#include <memory>
#include "ship.hpp"
#include "building.hpp"
#include "resources.hpp"
#include "string"

using namespace std;

class Player{
public:
std::vector<shared_ptr<Ship>> ships_;
std::vector<shared_ptr<Building>> buildings_;
Resources resources_;
std::string get_name() {return name_;}
void set_name(std::string name) {name_ = name;}

private:
	std::string name_;
};

typedef std::unique_ptr<Player> player_ptr;

#endif //PLAYER_HPP
