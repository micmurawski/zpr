#include "../game_order/game_order.hpp"
#include "building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include <memory>
#include "../game_order/order_decoder.hpp"
#include "game_object_factory.hpp"
#include "game_object.hpp"
#include "map_point.hpp"

using namespace std;



int main(){
	/*
	GameObjectFactory& factory = GameObjectFactory::get_instance();
	Ship::ID_ = factory.registerObject(Ship::create);
	MapPoint::ID_ = factory.registerObject(MapPoint::create);
	Resources::ID_ = factory.registerObject(Resources::create);
	
	Ship ship(12, 13);
	vector<string>vec;
	vec.push_back(ship.toString(2)); //the number in the function argument is players number
	
	Resources r(500);
	vec.push_back(r.toString(1)); //the number in the function argument is players number
	
	vector<unsigned int> connections;
	connections.push_back(3);
	connections.push_back(5);
	connections.push_back(8);
	connections.push_back(2);
	MapPoint point(10, connections, 4, 7, r);
	vec.push_back(point.toString(1));
	
	//function decode creates new GameState object that represents current situation in game
	shared_ptr<GameState> gamestate = factory.decode(vec);
	
	cout<<endl<<vec[0]<<endl;
	cout<<endl<<(gamestate->players_[2]->ships_[0]->toString())<<endl;
	cout<<endl<<vec[2]<<endl;
	cout<<endl<<(gamestate->map_points_[0]->toString())<<endl;
	cout<<endl<<vec[1]<<endl;
	cout<<endl<<(gamestate->players_[1]->resources_.toString())<<endl;
	*/
	/*
	vector<unsigned int> ship;
	ship.push_back(1);
	ship.push_back(7);
	ship.push_back(2);
	ship.push_back(9);
	ship.push_back(3);*/
	/*
	MoveOrder order(20, 40, ship);
	BuildOrder order2(30);
	CreateShipOrder order3 (40);*/
	//cout<<"\n" <<order.toString();
	//cout<<"\n" <<order2.toString();
	//cout<<"\n" <<order3.toString();
	
	//MoveOrder order3("<ships>#1#7#2#9#3</ships><destination>40</destination>");
	//CreateShipOrder order4("<destination>4</destination>");
	//OrderDecoder decoder;
	//cout<<order.toString()+order2.toString()+order3.toString();
	//decoder.decode(order.toString()+order2.toString()+order3.toString());
	/*cout<<endl <<"TEST";
	cout<<endl <<decoder.move_orders_[0]->toString()
		<<endl <<decoder.create_ship_orders_[0]->toString()
		<<endl <<decoder.build_orders_[0]->toString();*/
		
	Resources r(500);
	Building building(12);

	
	/*vector<unsigned int> connections;
	connections.push_back(3);
	connections.push_back(5);
	connections.push_back(8);
	connections.push_back(2);
	MapPoint point(10, connections, 4, 7, r);
	cout<<"point " <<point.toString();
	MapPoint point2;
	point2.loadFromString(point.toString());
	cout<<endl<<point2.toString();*/
	Player player("player");
	player.resources_=r;
	player.ships_.push_back(make_shared<Ship>(12,13));
	player.ships_.push_back(make_shared<Ship>(32,123));
	player.buildings_.push_back(make_shared<Building>(12));
	player.id_=3;
	cout<<player.toString();
	cout<<endl;
	cout<<endl;
	Player player2("");
	player2.loadFromString(player.toString());
	cout<<player2.toString();
	
	
	


	return 0;
}
