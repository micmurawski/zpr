#ifndef GAME_OBJECT_FACTORY_HPP
#define GAME_OBJECT_FACTORY_HPP

#include <vector>
#include <map>
#include "ship.hpp"
#include "../game_state/game_state.hpp"

using namespace std;
/**
 * Definicje typów wskaźników
 *
 */
typedef shared_ptr<GameObject> game_object_ptr;
typedef shared_ptr<GameObject> (*createGameObject)();
typedef map<unsigned int, createGameObject> func_map;
typedef shared_ptr<GameState> game_state_ptr;

/**
 * \class GameObjectFactory
 *
 * Definicja klasy GameObjectFactory jest klasą statyczną,fabryką obiektów typu GameObject.
 * \author $Author: Marcin Brzykcy, Michał Murawski $
 *
 */

class GameObjectFactory{
	public:
		/**
 		* Zwraca singleton klasy
		* GameObjectFactory is a singleton, so get_instance is used to get this object
 		*/
		static GameObjectFactory& get_instance(){return instance_;}
		/**
 		* Funkcja rejestruje obiekt w fabryce.
 		* \return zwraca liczbę reprezentującą obiekt
 		*/	
		unsigned int registerObject(createGameObject fun);
		/**
 		* Funkcja dekoduje Stan gry na podstawie stringa
 		* \return wskaźnik na GameState reprezentujący stan gry
 		*/	
		shared_ptr<GameState> decode(vector<string> vec);
	private:
		/**
 		* Funkcja tworząca obiekty gry
 		* \return zwraca wskaźnik na obiket gry
 		*/	
		game_object_ptr create(unsigned int type);
		//ID_ is used to generate new id's for registered objects
		static unsigned int ID_;
		//object_creators_ store pointers to functions used to generate object from string
		func_map objects_creators_;
		static GameObjectFactory instance_;
		GameObjectFactory() {};
		
		
	};
#endif //GAME_OBJECT_FACTORY_HPP
