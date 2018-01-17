#include "game_state.hpp"
#include "../get_regex_function.hpp"

using namespace std;

GameState::GameState(){
	//for (int i = 0; i<players_number; i++)
	//	players_.push_back(make_unique<Player>());
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

void GameState::removeShips(){
	for(player_ptr p: players_){
		p.get()->ships_.erase(
        remove_if(
        p.get()->ships_.begin(),
       	p.get()->ships_.end(),
        [](const shared_ptr<Ship>& ship_p){ return ship_p.get()->getHP()==0; }
        ),
        p.get()->ships_.end());
	}
}

std::string GameState::toString(){
    string data = "<game_state><players>";
    for(auto player : players_){
    data=data+player->toString();
    }
    data=data+"</players>";
    data=data+"<map_points>";
    for(auto point : map_points_){
    data=data+point->toString();
    }
    data =data+"</map_points></game_state>";
    return data;
}
void GameState::loadFromString(std::string data){
    players_.clear();
    map_points_.clear();
    //wczytywanie graczy
    string players = getRegex(data,"(?<=<players>)(.*)(?=</players>)");
    while(players.size()>0){
    string player_str = players.substr(players.find("<player>")+8, players.find("</player>")-8);
    shared_ptr<Player> player = make_shared<Player>("");
    player->loadFromString(player_str);
    players_.push_back(player);
    players = players.substr(players.find("</player>")+9);
        }

    //wczytywanie punktow
    string points = getRegex(data,"(?<=<map_points>)(.*)(?=</map_points>)");
    while(points.size()>0){
    string point_str = points.substr(points.find("<map_point>")+11, points.find("</map_point>")-11);
    shared_ptr<MapPoint> point = make_shared<MapPoint>();
    point->loadFromString(point_str);
    map_points_.push_back(point);
    points = points.substr(points.find("</map_point>")+12);
        }


}
