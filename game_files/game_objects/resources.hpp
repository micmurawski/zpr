#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include "game_object.hpp"
#include <string>
#include <memory>


class Resources : public GameObject{
	public:
	Resources(int metal=0) : metal_(metal){};
	unsigned int metal_;
	
	//this method is used if we want to get string containing 
	//only data of variables, withoud additional information
	std::string toStringDataOnly();
	
	virtual std::string toString(unsigned int player_id = 0);
	virtual void loadFromString (std::string data);
	//used to determine type in GameObjectsFactory
	virtual unsigned int getType();
	//used to create objects in GameObjectsFactory
	static std::shared_ptr<GameObject> create();
	//ID needed for ObjectFactory
	static unsigned int ID_;
};

#endif //RESOURCES_HPP
