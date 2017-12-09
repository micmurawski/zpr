#ifndef MAP_POINT_HPP
#define MAP_POINT_HPP

#include <vector>
#include <memory>
#include "resources.hpp"
#include "building.hpp"

class Planet{
	public:
		Planet(const Planet&) = default;
		Planet(Resources resources): resources_(resources){}
		const Resources& get_resources() const {return resources_;}
	private:
		Resources resources_;
	};
	
class MapPoint{
public:
		MapPoint(int id, std::vector<unsigned int>& connections, const Planet& planet, int x, int y): 
		id_(id), connections_(connections), x_(x), y_(y) {planet_ = std::make_unique<Planet>(planet);}
		unsigned int getId() const {return id_;} 
		unsigned int getX() const {return x_;} 
		unsigned int gety() const {return y_;} 
		bool hasBuilding() const{ if(building_) return true; else return false;}
		bool hasPlanet() const{ if(planet_) return true; else return false;}
		const Planet& getPlanet() const {return *planet_;}
		const Building& getBuilding() const {return *building_;}
		void build (Building building) {building_ = std::make_unique<Building>(building);}
		
private:
	unsigned int id_;
	std::vector<unsigned int> connections_;
	std::unique_ptr<Planet> planet_;
	std::unique_ptr<Building> building_;
	unsigned int x_;
	unsigned int y_;
	};
	
#endif //MAP_POINT_HPP


