#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "game_object.hpp"

class Building : public GameObject{
public:
    Building(int point_id_=0): point_id_(0){}
	unsigned int getMapPointId(){return point_id_;}
private:
	unsigned int point_id_;
};

#endif //BUILDING_HPP
