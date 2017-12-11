#ifndef MAP_POINT_HPP
#define MAP_POINT_HPP

#include <vector>
#include <memory>
#include "resources.hpp"
#include "building.hpp"
#include "resources.hpp"

class MapPoint{
public:
		MapPoint(int id, std::vector<unsigned int>& connections, int x, int y, Resources resources): 
		id_(id), connections_(connections), x_(x), y_(y) {}
		unsigned int getId() const {return id_;} 
		unsigned int getX() const {return x_;} 
		unsigned int gety() const {return y_;} 
		
		
private:
	unsigned int id_;
	std::vector<unsigned int> connections_;
	Resources resources_;
	unsigned int x_;
	unsigned int y_;
	};
	
#endif //MAP_POINT_HPP


