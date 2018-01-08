#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <memory>
#include <string>
#include "game_object.hpp"


class Ship : public GameObject{
public:
	Ship(unsigned int id=0, unsigned int map_point_id=0): hp_(80), id_(id), map_point_id_(map_point_id) {}
	virtual void modifyHP(int hp);
	virtual int getDamage() {return 10;}
	virtual std::string toString(unsigned int player_id = 0);
	virtual void loadFromString (std::string data);
	//used to determine type in GameObjectsFactory
	virtual unsigned int getType();
	//used to create objects in GameObjectsFactory
	static std::shared_ptr<GameObject> create();
	//ID is needed for ObjectFactory
	static unsigned int ID_;
	//returns position of the ship
	unsigned int getMapPointId(){return map_point_id_;}
    //returns id of the individual ship
    unsigned int getId(){return id_;}

private:
	unsigned int hp_;
	//map_point_id is ship location
	unsigned int map_point_id_;
	//id of the individual ship
	unsigned int id_;

	};
	

#endif //SHIP_HPP
