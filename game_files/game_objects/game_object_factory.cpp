#include "game_object_factory.hpp"
#include <regex>
#include "ship.hpp"

using namespace std;

shared_ptr<GameState> GameObjectFactory::decode(vector<string> vec){
	game_state_ptr game_state= make_shared<GameState>(4);
	for(auto str : vec){	
		//erasing first "#" from the beggining of string
		string s = str.substr(1);
		//getting type of object from string
		regex r("#");
		smatch m; 
		regex_search(s, m, r); 
		int split_on = m.position();
		string type_s = (s.substr(0, split_on)); 
		//splitting remaining string into players_id and data
		//data is than used to generate object
		string temp  = s.substr(split_on + m.length());
		regex_search(temp, m, r); 
		split_on = m.position();
		string player_id_s = (temp.substr(0, split_on));
		string data  = temp.substr(split_on + m.length()); 
		int type = stoi(type_s);
		int player_id = stoi(player_id_s);
		//creating new object based on type
		//then loading it from string data
		//and passing it to game state object
		game_object_ptr object = create(type);
		if(object!=nullptr){
			object->player_id_ = player_id;
			object->loadFromString(data);
			game_state->accept(object);	
			} else
			cerr<<"failed to read object from string" <<str;
		
		}
	return game_state;
	}
	
	unsigned int GameObjectFactory::registerObject (createGameObject fun){
	objects_creators_.insert(std::pair<unsigned int, createGameObject>(++ID_,fun));
	return ID_;
	}
	
	game_object_ptr GameObjectFactory::create(unsigned int type){
		//Creating new object based on id
		func_map::iterator it=objects_creators_.find(type);
		if (it!=objects_creators_.end()){
			game_object_ptr ptr = (it->second)();
			//game_object_ptr ptr= make_shared<Ship> ();
			return ptr;//make_shared<Ship> ();
			}
		return nullptr;
		}
	
	unsigned int GameObjectFactory::ID_=1;
	GameObjectFactory GameObjectFactory::instance_;
