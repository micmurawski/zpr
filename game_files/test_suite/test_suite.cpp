#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Suites
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include "../game_engine/game_client.hpp"
#include "../game_engine/game_server.hpp"
#include "../game_order/game_order.hpp"
#include "../game_objects/building.hpp"
#include <cstdio>
#include <iostream>
#include <vector>
#include "../game_order/order_decoder.hpp"
#include "../game_objects/game_object_factory.hpp"
#include "../game_objects/game_object.hpp"
#include "../game_objects/map_point.hpp"
#include <unistd.h>

using namespace boost::unit_test;


  

std::string connectedPlayerTest(){
  GameServer::get().start("127.0.0.1",3002);
  GameClient gameClient;
  gameClient._name="Amadeusz";
  gameClient.connect("127.0.0.1",3002);
  gameClient.join();
  usleep(2000);
  return GameServer::get().getPlayers()[0]->name_+" "+GameServer::get().getPlayers()[0]->host_;
}


bool gameObjectsEncodeDecode(){
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

  return vec[0]==(gamestate->players_[2]->ships_[0]->toString())&&
   (vec[2]==(gamestate->map_points_[0]->toString()))&&
	(vec[1]==(gamestate->players_[1]->resources_.toString()));

}




  BOOST_AUTO_TEST_SUITE(TestGry)
  BOOST_AUTO_TEST_CASE(Funkcje)
  {
      BOOST_CHECK(connectedPlayerTest()=="Amadeusz 127.0.0.1");
      BOOST_CHECK(gameObjectsEncodeDecode()==true);
  }
  BOOST_AUTO_TEST_SUITE_END()


