#ifndef MAP_POINT_HPP
#define MAP_POINT_HPP

#include <vector>
#include <memory>
#include "resources.hpp"
#include "building.hpp"
#include "resources.hpp"
#include <memory>
#include "game_object.hpp"
#include "resources.hpp"
#include <vector>

class MapPoint : public GameObject{
public:
	MapPoint(){};
	MapPoint(int id, std::vector<unsigned int>& connections, int x, int y, Resources resources): 
	id_(id), connections_(connections), x_(x), y_(y) {resources_ = resources;}
	unsigned int getId() const {return id_;} 
	unsigned int getX() const {return x_;} 
	unsigned int gety() const {return y_;} 
	
	
	virtual std::string toString(unsigned int player_id = 0);
	virtual void loadFromString (std::string data);
	//used to determine type in GameObjectsFactory
	virtual unsigned int getType();
	//used to create objects in GameObjectsFactory
	static std::shared_ptr<GameObject> create();
	//ID needed for ObjectFactory
	static unsigned int ID_;
		
		
private:
	
	//id of the individual point
	unsigned int id_;
	//vector of id's of the connected points
	std::vector<unsigned int> connections_;
	unsigned int x_;
	unsigned int y_;	
	Resources resources_;
	};
	
#endif //MAP_POINT_HPP


