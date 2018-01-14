#include "game_state.hpp"

using namespace std;

GameState::GameState(unsigned int players_number){
	for (int i = 0; i<players_number; i++)
		players_.push_back(make_unique<Player>());
	}

void GameState::accept(game_object_ptr object){
	
	if(object->getType() == map_point_prototype_.getType())
		map_points_.push_back(dynamic_pointer_cast<MapPoint>(object));
	else if(object->getType() == ship_prototype_.getType())
		players_[object->player_id_]->ships_.push_back(dynamic_pointer_cast<Ship> (object));
	else if(object->getType() == building_prototype_.getType())
		players_[object->player_id_]->buildings_.push_back(dynamic_pointer_cast<Building> (object));
	else if(object->getType() == resources_prototype_.getType())
		players_[object->player_id_]->resources_ = *(dynamic_pointer_cast<Resources> (object));
	}

map_point_ptr GameState::getPointById(unsigned int id){
    //std::cerr<<"\n" <<id;
    for (auto p : map_points_){
        //test
        //std::cerr<<"\n" <<p->getId();
		if(p->getId() == id)
			return p;
		}
	return nullptr;
	}
	
int GameState::MapPointOwnerId(unsigned int map_point_id){
	for(auto p : players_){
		for(auto ship : p->ships_){
			if(ship->getMapPointId()==map_point_id)
				return p->getId();
			}
		for(auto building : p->buildings_){
			if(building->getMapPointId()==map_point_id)
				return p->getId();	
			}
		}
	return -1;
	}

int GameState::WhoHasFleet(unsigned int map_point_id){
		for(auto p : players_){
		for(auto ship : p->ships_){
			if(ship->getMapPointId()==map_point_id)
				return p->getId();
			}
		}
	return -1;
	}

std::vector<std::shared_ptr<Ship>> GameState::FleetOnPoint(unsigned int map_point_id){
    std::vector<std::shared_ptr<Ship>> vec;

    for(auto p : players_){
    for(auto ship : p->ships_){
        if(ship->getMapPointId()==map_point_id)
            vec.push_back(ship);
        }
    }
    return vec;
}

int GameState::WhoHasBuilding(unsigned int map_point_id){
    for(auto p : players_){
    for(auto building : p->buildings_){
        if(building->getMapPointId()==map_point_id)
            return p->getId();
        }
    }
return -1;
}

bool GameState::isConnection(unsigned int map_point1, unsigned int map_point2){
    map_point_ptr p1 = getPointById(map_point1);
    std::vector<unsigned int> v = p1->getConnections();

    for(auto i : v){
        if(i == map_point2)
            return true;
    }
    return false;

}
