#ifndef GAME_OBJECT_FACTORY_HPP
#define GAME_OBJECT_FACTORY_HPP

#include <vector>
#include <map>
#include "ship.hpp"
#include "game_state.hpp"

using namespace std;

typedef shared_ptr<GameObject> game_object_ptr;
typedef shared_ptr<GameObject> (*createGameObject)();
typedef map<unsigned int, createGameObject> func_map;
typedef shared_ptr<GameState> game_state_ptr;



class GameObjectFactory{
	public:
		//GameObjectFactory is a singleton, so get_instance is used to get this object
		static GameObjectFactory& get_instance(){return instance_;}
		//it takes pointer to the function that creates object and returns id_ that
		//registered objects store in their static id_ field
		unsigned int registerObject(createGameObject fun);
		shared_ptr<GameState> decode(vector<string> vec);
	private:
		game_object_ptr create(unsigned int type);
		//ID_ is used to generate new id's for registered objects
		static unsigned int ID_;
		//object_creators_ store pointers to functions used to generate object from string
		func_map objects_creators_;
		static GameObjectFactory instance_;
		GameObjectFactory() {};
		
		
	};
#endif //GAME_OBJECT_FACTORY_HPP
